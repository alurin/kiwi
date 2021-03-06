/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "LlvmEmitter.hpp"
#include "../TypeImpl.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Argument.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/Support/Cast.hpp"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Module.h>

using namespace kiwi;
using namespace kiwi::codegen;

//===--------------------------------------------------------------------------------------------------------------===//
//    Utils
//===--------------------------------------------------------------------------------------------------------------===//
namespace {
    llvm::ConstantInt* makeConstantInt(llvm::LLVMContext& context, int32_t value) {
        llvm::APInt cst(32, value, false);
        return llvm::ConstantInt::get(context, cst);
    }
}


UpcastConverter::UpcastConverter(ObjectPtr type)
: m_type(type) {
}

LlvmCallEmitter::LlvmCallEmitter(MethodPtr method, TypePtr returnType)
: m_method(method), m_returnType(returnType) {

}

// constructor
LlvmZeroUnaryOperator::LlvmZeroUnaryOperator(llvm::Instruction::BinaryOps opcode, TypePtr type)
: m_opcode(opcode), m_type(type) { }

// constructor
LlvmBinaryOperator::LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode, TypePtr type)
: m_opcode(opcode), m_type(type) { }

// constructor
LlvmIntegerCompareOperator::LlvmIntegerCompareOperator(llvm::CmpInst::Predicate predicate, ContextPtr context)
: m_predicate(predicate), m_context(context) { }

LlvmStringCompareOperator::LlvmStringCompareOperator(llvm::CmpInst::Predicate predicate, ContextPtr context)
: m_predicate(predicate), m_context(context) { }

// emit instruction for interger unary operator
ValueBuilder LlvmZeroUnaryOperator::emit(BlockBuilder block, const ExpressionVector& values) {
    llvm::APInt cst(32, 0, false);
    llvm::ConstantInt* zero = llvm::ConstantInt::get(block.getContext(), cst);
    llvm::Value* result = llvm::BinaryOperator::Create(m_opcode, zero, values[0].getValue(), "", block.getBlock());
    return ValueBuilder(block, result, m_type.lock());
}

// emit instruction for binary operator
ValueBuilder LlvmBinaryOperator::emit(BlockBuilder block, const ExpressionVector& values) {
    llvm::Value* result = llvm::BinaryOperator::Create(m_opcode, values[0].getValue(), values[1].getValue(), "", block.getBlock());
    return ValueBuilder(block, result, m_type.lock());
}

// emit instruction for binary operator
ValueBuilder LlvmIntegerCompareOperator::emit(BlockBuilder block, const ExpressionVector& values) {
    llvm::Value* result = new llvm::ICmpInst(*(block.getBlock()), m_predicate, values[0].getValue(), values[1].getValue(), "");
    return ValueBuilder(block, result, BooleanType::get(m_context.lock()));
}

// emit instruction for binary operator
ValueBuilder LlvmStringCompareOperator::emit(BlockBuilder block, const ExpressionVector& values) {
    // create stub for u_strCompare
    llvm::Module*       module = block.getModule();
    llvm::LLVMContext& context = block.getContext();
    llvm::Type*     lengthType = llvm::IntegerType::get(context, 32);
    llvm::Type*     charType   = llvm::IntegerType::get(context, 16)->getPointerTo();
    llvm::Type*     boolType   = llvm::IntegerType::get(context, 8);

    /// kiwi_string_compare(const UChar *s1, int32_t length1, const UChar *s2, int32_t length2);
    llvm::Function* compare  = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_string_compare", lengthType, charType, lengthType, charType, lengthType, NULL));

    // create variable for compare
    llvm::APInt cst(32, 0, false);
    llvm::ConstantInt* zero = llvm::ConstantInt::get(block.getContext(), cst);

    cst = llvm::APInt(32, 1, false);
    llvm::ConstantInt* one = llvm::ConstantInt::get(block.getContext(), cst);

    cst = llvm::APInt(8, 0, false);
    llvm::ConstantInt* falseBool = llvm::ConstantInt::get(block.getContext(), cst);

    // prepare GetElementPtrInst indexes
    std::vector<llvm::Value*> lengthIdx; // length
    lengthIdx.push_back(zero);
    lengthIdx.push_back(zero);

    std::vector<llvm::Value*> bufferIdx; // buffer
    bufferIdx.push_back(zero);
    bufferIdx.push_back(one);

    // find first string for method
    llvm::Value* string1   = llvm::GetElementPtrInst::CreateInBounds(values[0].getValue(), makeArrayRef(bufferIdx), "string1", block.getBlock());
    llvm::Value* position1 = llvm::GetElementPtrInst::CreateInBounds(values[0].getValue(), makeArrayRef(lengthIdx), "", block.getBlock());
    llvm::Value* length1   = new llvm::LoadInst(position1, "length1", block.getBlock());
    string1                = new llvm::BitCastInst(string1, charType, "", block.getBlock());

    // find first string for method
    llvm::Value* string2   = llvm::GetElementPtrInst::CreateInBounds(values[1].getValue(), makeArrayRef(bufferIdx), "string2", block.getBlock());
    llvm::Value* position2 = llvm::GetElementPtrInst::CreateInBounds(values[1].getValue(), makeArrayRef(lengthIdx), "", block.getBlock());
    llvm::Value* length2   = new llvm::LoadInst(position2, "length2", block.getBlock());
    string2                = new llvm::BitCastInst(string2, charType, "", block.getBlock());

    // collect arguments
    std::vector<llvm::Value*> args;
    args.push_back(string1);
    args.push_back(length1);
    args.push_back(string2);
    args.push_back(length2);
    args.push_back(falseBool);

    // compute string compare and return result
    llvm::Value* value  = llvm::CallInst::Create(compare, makeArrayRef(args), "", block.getBlock());
    llvm::Value* result = new llvm::ICmpInst(*(block.getBlock()), m_predicate, zero, value, "");
    return ValueBuilder(block, result, BooleanType::get(m_context.lock()));
}

ValueBuilder LlvmIntegerPrintOperator::emit(BlockBuilder block, const ExpressionVector& values) {
    llvm::Module*       module = block.getModule();
    llvm::LLVMContext& context = block.getContext();
    llvm::Type*       voidType = llvm::Type::getVoidTy(context);
    llvm::Type*           type = values[0].getType()->getMetadata()->getBackendVariableType();

    llvm::Function* print   = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_print_integer", voidType, type, NULL));

    std::vector<llvm::Value*> args;
    args.push_back(values[0].getValue());

    llvm::CallInst::Create(print, makeArrayRef(args), "", block.getBlock());

    return ValueBuilder(block, values[0].getValue(), values[0].getType());
}

ValueBuilder LlvmBoolPrintOperator::emit(BlockBuilder block, const ExpressionVector& values) {
    llvm::Module*       module = block.getModule();
    llvm::LLVMContext& context = block.getContext();
    llvm::Type*       voidType = llvm::Type::getVoidTy(context);
    llvm::Type*           type = values[0].getType()->getMetadata()->getBackendVariableType();

    llvm::Function* print   = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_print_bool", voidType, type, NULL));

    std::vector<llvm::Value*> args;
    args.push_back(values[0].getValue());

    llvm::CallInst::Create(print, makeArrayRef(args), "", block.getBlock());

    return ValueBuilder(block, values[0].getValue(), values[0].getType());
}

ValueBuilder LlvmCharPrintOperator::emit(BlockBuilder block, const ExpressionVector& values) {
    llvm::Module*       module = block.getModule();
    llvm::LLVMContext& context = block.getContext();
    llvm::Type*       voidType = llvm::Type::getVoidTy(context);
    llvm::Type*           type = values[0].getType()->getMetadata()->getBackendVariableType();

    llvm::Function* print   = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_print_char", voidType, type, NULL));

    std::vector<llvm::Value*> args;
    args.push_back(values[0].getValue());

    llvm::CallInst::Create(print, makeArrayRef(args), "", block.getBlock());

    return ValueBuilder(block, values[0].getValue(), values[0].getType());
}

// emit print for string
ValueBuilder LlvmStringPrintOperator::emit(BlockBuilder block, const ExpressionVector& values) {
    // create stub for u_strCompare
    llvm::Module*       module = block.getModule();
    llvm::LLVMContext& context = block.getContext();
    llvm::Type*     lengthType = llvm::IntegerType::get(context, 32);
    llvm::Type*     charType   = llvm::IntegerType::get(context, 16)->getPointerTo();
    llvm::Type*     voidType   = llvm::Type::getVoidTy(context);

    /// kiwi_print_string(const UChar *s, int32_t length);
    llvm::Function* print   = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_print_string", voidType, charType, lengthType, NULL));

    LlvmStringEmitter string;
    block = string.emit(block, values[0]);

    // collect arguments
    std::vector<llvm::Value*> args;
    args.push_back(string.getBufferValue());
    args.push_back(string.getLengthValue());

    // compute string compare and return result
    llvm::CallInst::Create(print, makeArrayRef(args), "", block.getBlock());
    return ValueBuilder(block, values[0].getValue(), values[0].getType());
}

/// emit reduce string as size and buffer
BlockBuilder LlvmStringEmitter::emit(BlockBuilder block, const ValueBuilder value) {
    llvm::Module*       module = block.getModule();
    llvm::LLVMContext& context = block.getContext();
    llvm::Type*     lengthType = llvm::IntegerType::get(context, 32);
    llvm::Type*     charType   = llvm::IntegerType::get(context, 16)->getPointerTo();

    // create variable for compare
    llvm::APInt cst(32, 0, false);
    llvm::ConstantInt* zero = llvm::ConstantInt::get(block.getContext(), cst);

    cst = llvm::APInt(32, 1, false);
    llvm::ConstantInt* one = llvm::ConstantInt::get(block.getContext(), cst);

    // prepare GetElementPtrInst indexes
    std::vector<llvm::Value*> lengthIdx; // length
    lengthIdx.push_back(zero);
    lengthIdx.push_back(zero);

    std::vector<llvm::Value*> bufferIdx; // buffer
    bufferIdx.push_back(zero);
    bufferIdx.push_back(one);
    // bufferIdx.push_back(zero);

    // find first string for method
    llvm::Value* length = llvm::GetElementPtrInst::Create(value.getValue(), makeArrayRef(lengthIdx), "", block.getBlock());
    length              = new llvm::LoadInst(length, "length", block.getBlock());
    llvm::Value* buffer = llvm::GetElementPtrInst::Create(value.getValue(), makeArrayRef(bufferIdx), "", block.getBlock());
    buffer              = new llvm::BitCastInst(buffer, charType, "buffer", block.getBlock());

    // store and return
    m_lengthValue = length;
    m_bufferValue = buffer;
    return block;
}

// emit IR instruction for string concatenate
ValueBuilder LlvmStringConcatenate::emit(BlockBuilder block, const ExpressionVector& values) {

}

// emit IR instruction for string substraction
ValueBuilder LlvmStringSubtraction::emit(BlockBuilder block, const ExpressionVector& values) {
    if (values.size() != 2 && values.size() != 3) {
        BOOST_THROW_EXCEPTION(Exception()
            << exception_message("Not implemented"));
    }

    ContextPtr         t_context = block.getNativeContext();
    llvm::Module*       module = block.getModule();
    llvm::LLVMContext& context = block.getContext();
    llvm::Type*     lengthType = llvm::IntegerType::get(context, 32);
    llvm::Type*     charType   = llvm::IntegerType::get(context, 16);
    llvm::Type*     bufferType = llvm::IntegerType::get(context, 16)->getPointerTo();
    llvm::Type*     voidType   = llvm::Type::getVoidTy(context);

    LlvmStringEmitter string;
    block = string.emit(block, values[0]);

    // collect arguments
    std::vector<llvm::Value*> args;
    args.push_back(string.getBufferValue());
    args.push_back(string.getLengthValue());

    //
    llvm::Function* substraction = 0;
    TypePtr returnType;

    // collect types and functions
    if (values.size() == 2) {           /// substraction of character from string
        returnType   = CharType::get(t_context);

        substraction = llvm::dyn_cast<llvm::Function>(
            module->getOrInsertFunction(
                "kiwi_subchar",
                charType,
                bufferType,
                lengthType,
                lengthType,
                NULL
            )
        );

        args.push_back(values[1].getValue());
    } else if (values.size() == 3) {    /// substraction of substring from string
        returnType   = StringType::get(t_context);

        substraction = llvm::dyn_cast<llvm::Function>(
            module->getOrInsertFunction(
                "kiwi_substring",
                returnType->getMetadata()->getBackendVariableType(),
                bufferType,
                lengthType,
                lengthType,
                lengthType,
                NULL
            )
        );

        args.push_back(values[1].getValue());
        args.push_back(values[2].getValue());
    }

    // compute string compare and return result
    llvm::CallInst* returnValue = llvm::CallInst::Create(substraction, makeArrayRef(args), "", block.getBlock());
    return ValueBuilder(block, returnValue, returnType);
}

// emit IR instruction for call method
ValueBuilder LlvmCallEmitter::emit(BlockBuilder block, const ExpressionVector& values) {
    std::vector<llvm::Value*> largs;
    MethodPtr method = m_method.lock();

    // collect arguments
    int j = 0;
    for (ExpressionVector::const_iterator i = values.begin(); i != values.end(); ++i, ++j) {
        ValueBuilder expr = *i;

        /// cast to actual type
        ArgumentPtr arg = method->getArgument(j);
        TypePtr exceptedType = arg->getType();
        TypePtr actualType   = expr.getType();

        if (exceptedType != actualType) {
            ObjectPtr objType = dyn_cast<ObjectType>(exceptedType);
            if (objType == 0) {
                BOOST_THROW_EXCEPTION(Exception()
                    << exception_message("Not implemented"));
            }
            expr  = UpcastConverter(objType).emitCast(block, expr);
            block = expr;
        }

        largs.push_back(expr.getValue());
    }

    // forced update for vtable
    method->getOwnerType()->getMetadata()->getVirtualTable();
    kiwi_assert(method->getPosition() != -1, "Location for method not founded");

    // constants
    llvm::APInt cst(32, 0, false);
    llvm::ConstantInt* zero = llvm::ConstantInt::get(block.getContext(), cst);
    cst = llvm::APInt(32, method->getPosition(), false);
    llvm::ConstantInt* pos = llvm::ConstantInt::get(block.getContext(), cst);

    // load vtable
    std::vector<llvm::Value*> bufferIdx; // buffer
    bufferIdx.push_back(zero);
    bufferIdx.push_back(zero);
    llvm::Value* vtable = llvm::GetElementPtrInst::CreateInBounds(largs[0], makeArrayRef(bufferIdx), "vtable_pos", block.getBlock());

    // dereference vtable
    vtable = new llvm::LoadInst(vtable, "vtable_val", block.getBlock());
    vtable = new llvm::LoadInst(vtable, "vtable", block.getBlock());

    // load vslot
    bufferIdx.clear();
    bufferIdx.push_back(zero);
    bufferIdx.push_back(pos);
    llvm::Value* vslot = llvm::GetElementPtrInst::Create(vtable, makeArrayRef(bufferIdx), "vslot_pos", block.getBlock());
    vslot = new llvm::LoadInst(vslot, "vslot_val", block.getBlock());

    // {
    //     llvm::Value* typeValue  = values[0].getType()->getMetadata()->getBackendPointer();
    //     llvm::Type* pointerType = llvm::IntegerType::get(block.getContext(), 8)->getPointerTo();
    //     llvm::Function* dump_pointer = llvm::dyn_cast<llvm::Function>(block.getModule()->getOrInsertFunction("kiwi_dump_ptr", llvm::Type::getVoidTy(block.getContext()), pointerType, typeValue->getType(), NULL));

    //     std::vector<llvm::Value*> args;
    //     args.push_back(new llvm::BitCastInst(vslot, pointerType, "", block.getBlock()));
    //     args.push_back(typeValue);
    //     llvm::Value* value = llvm::CallInst::Create(dump_pointer, makeArrayRef(args), "", block.getBlock());
    // }

    // return result of call
    llvm::Type* funcType = method->getFunction()->getFunctionType();
    vslot = new llvm::BitCastInst(vslot, funcType->getPointerTo(), "vslot", block.getBlock());
    llvm::Value* result = llvm::CallInst::Create(vslot, llvm::makeArrayRef(largs), "", block.getBlock());
    return ValueBuilder(block, result, m_returnType.lock());
}

// emit IR instruction for binary operation
ValueBuilder LlvmCtorEmitter::emit(BlockBuilder bloc, const ExpressionVector& values) {
    return values[0];
}

/// emit IR instruction for binary operation
ValueBuilder LlvmUpcast::emit(BlockBuilder bloc, const ExpressionVector& values) {
    BOOST_THROW_EXCEPTION(Exception()
            << exception_message("Not implemented"));
}

/// Convert from variable to this
ValueBuilder UpcastConverter::emitToThis(BlockBuilder block, ValueBuilder variableValue) {
    return ValueBuilder(block, variableValue.getValue(), variableValue.getType());
}

/// Convert from this to variable
ValueBuilder UpcastConverter::emitFromThis(BlockBuilder block, ValueBuilder thisValue) {
    return emitCast(block, thisValue);
}

/// Convert from this to variable
ValueBuilder UpcastConverter::emitCast(BlockBuilder block, ValueBuilder thisValue) {
    llvm::LLVMContext& context = block.getContext();
    llvm::Module* module       = block.getModule();
    llvm::Type* pointerType    = llvm::IntegerType::get(context, 8)->getPointerTo();

    llvm::Function* cast       = llvm::dyn_cast<llvm::Function>(module->getOrInsertFunction("kiwi_up_cast", pointerType, pointerType, pointerType, NULL));
    llvm::Value* typeValue     = m_type.lock()->getMetadata()->getBackendPointer();

    std::vector<llvm::Value*> args;
    args.push_back(thisValue.getValue());
    args.push_back(typeValue);
    llvm::Value* value = llvm::CallInst::Create(cast, makeArrayRef(args), "", block.getBlock());
    llvm::Value* castValue = new llvm::BitCastInst(value, thisValue.getType()->getMetadata()->getBackendVariableType(), "this", block.getBlock());
    return ValueBuilder(block, castValue, thisValue.getType());
}
