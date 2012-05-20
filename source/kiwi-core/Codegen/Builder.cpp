/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Builder.hpp"
#include "Emitter.hpp"
#include "../ModuleImpl.hpp"
#include "../TypeImpl.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Argument.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Support/Cast.hpp"
#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/BasicBlock.h"
#include "llvm/Instructions.h"
#include "llvm/Constants.h"
#include <llvm/Support/IRBuilder.h>

#define EMPTY_WHILE_WRAP(_stmt_) do { _stmt_ } while(0)

#define BUILDER_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_nativeModule,  "Builder must have Kiwi module"); \
        kiwi_assert(m_nativeContext, "Builder must have Kiwi context"); \
        kiwi_assert(m_module,        "Builder must have LLVM module"); \
        kiwi_assert(m_context,       "Builder must have LLVM context"); \
    )

#define BUILDER_FUNCTION_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_nativeCallable || m_func, "FunctionBuilder must have Kiwi callable or LLVM function"); \
        kiwi_assert(m_nativeOwner,    "FunctionBuilder must have Kiwi owner type"); \
    )

#define BUILDER_BLOCK_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(getFunction(),  "BlockBuilder must have LLVM function");   \
        kiwi_assert(m_block, "BlockBuilder must have LLVM basic block"); \
        kiwi_assert(m_block->getParent() == getFunction(), "Builder must have block from the same function"); \
    )

#define BUILDER_VALUE_ASSERT() EMPTY_WHILE_WRAP( \
        kiwi_assert(m_value, "ValueBuilder must have LLVM value"); \
        kiwi_assert(m_type,  "ValueBuilder must have Kiwi type");   \
    )

using namespace kiwi;

//===--------------------------------------------------------------------------------------------------------------===//
//    Utils
//===--------------------------------------------------------------------------------------------------------------===//
namespace {
    llvm::ConstantInt* makeConstantInt(llvm::LLVMContext& context, int32_t value) {
        llvm::APInt cst(32, value, false);
        return llvm::ConstantInt::get(context, cst);
    }
}

//===--------------------------------------------------------------------------------------------------------------===//
//    Constructors and assignments
//===--------------------------------------------------------------------------------------------------------------===//
Builder::Builder(ModulePtr module)
: m_nativeModule(module), m_module(0), m_context(0) {
    m_nativeContext = m_nativeModule->getContext();
    m_module        = m_nativeModule->getMetadata()->getBackendModule();
    m_context       = &m_module->getContext();
    BUILDER_ASSERT();
}

// Copy constructor
Builder::Builder(const Builder& builder)
: m_nativeModule(builder.m_nativeModule), m_module(0), m_context(0) {
    m_nativeContext = m_nativeModule->getContext();
    m_module        = m_nativeModule->getMetadata()->getBackendModule();
    m_context       = &m_module->getContext();
    BUILDER_ASSERT();
}

// Assigment
Builder& Builder::operator=(const Builder& builder) {
    if (this != &builder) {
        m_nativeModule  = builder.m_nativeModule;
        m_nativeContext = builder.m_nativeContext;
        m_module        = builder.m_module;
        m_context       = builder.m_context;
        BUILDER_ASSERT();
    }
    return *this;
}

// Constructor
FunctionBuilder::FunctionBuilder(MethodPtr analog)
: Builder(analog->getOwnerType()->getModule()), m_nativeCallable(analog)
, m_nativeOwner(analog->getOwnerType()) , m_func(0) {
    BUILDER_FUNCTION_ASSERT();
}

// Constructor
FunctionBuilder::FunctionBuilder(TypePtr type, llvm::Function* func)
: Builder(type->getModule()), m_nativeOwner(type), m_func(func) {
    BUILDER_FUNCTION_ASSERT();
}

// Copy constructor
FunctionBuilder::FunctionBuilder(const FunctionBuilder& builder)
: Builder(builder), m_func(builder.m_func), m_nativeCallable(builder.m_nativeCallable), m_nativeOwner(builder.m_nativeOwner) {
    BUILDER_FUNCTION_ASSERT();
}

// Assigment
FunctionBuilder& FunctionBuilder::operator=(const FunctionBuilder& builder) {
    if (this != &builder) {
        Builder::operator=(builder);
        m_nativeCallable = builder.m_nativeCallable;
        m_nativeOwner    = builder.m_nativeOwner;
        m_func           = builder.m_func;

        BUILDER_FUNCTION_ASSERT();
    }
    return *this;
}

// constructor
BlockBuilder::BlockBuilder(const FunctionBuilder& builder, llvm::BasicBlock* block)
: FunctionBuilder(builder), m_block(block) {
    BUILDER_BLOCK_ASSERT();
}

// Copy constructor
BlockBuilder::BlockBuilder(const BlockBuilder& builder)
: FunctionBuilder(builder), m_block(builder.m_block) {
    BUILDER_BLOCK_ASSERT();
}

// Assigment
BlockBuilder& BlockBuilder::operator=(const BlockBuilder& builder) {
    if (this != &builder) {
        FunctionBuilder::operator=(builder);
        m_block = builder.m_block;
        BUILDER_BLOCK_ASSERT();
    }
    return *this;
}

// constructor
ValueBuilder::ValueBuilder(const BlockBuilder& builder, llvm::Value* value, TypePtr type)
: BlockBuilder(builder), m_value(value), m_type(type) {
    BUILDER_VALUE_ASSERT();
}

// Copy constructor
ValueBuilder::ValueBuilder(const ValueBuilder& builder)
: BlockBuilder(builder), m_value(builder.m_value), m_type(builder.m_type) {
    BUILDER_VALUE_ASSERT();
}

// Assigment
ValueBuilder& ValueBuilder::operator=(const ValueBuilder& builder) {
    if (this != &builder) {
        FunctionBuilder::operator=(builder);
        m_value = builder.m_value;
        m_type  = builder.m_type;

        BUILDER_VALUE_ASSERT();
    }
    return *this;
}

//===--------------------------------------------------------------------------------------------------------------===//
//    Function builder methods
//===--------------------------------------------------------------------------------------------------------------===//

// emit method type
llvm::FunctionType* FunctionBuilder::getFunctionType() const {
    if (m_func) {
        return m_func->getFunctionType();
    }

    // collect arguments types
    std::vector<llvm::Type*> args;
    llvm::Type* returnType = m_nativeCallable->getReturnType()->getMetadata()->getBackendVariableType();

    // collect explicit arguments
    int j = 0;
    for (std::vector<ArgumentPtr>::const_iterator i = m_nativeCallable->arg_begin(); i != m_nativeCallable->arg_end(); ++i, ++j) {
        ArgumentPtr arg = *i;
        if (j) {
            args.push_back(arg->getType()->getMetadata()->getBackendVariableType());
        } else {
            args.push_back(arg->getType()->getMetadata()->getBackendThisType());
        }
    }

    // generate type and yeld
    return llvm::FunctionType::get(returnType, llvm::makeArrayRef(args), false);
}

// emit method definition
llvm::Function* FunctionBuilder::getFunction() const {
    // generate function, if this is required
    if (!m_func) {
        kiwi_assert(m_nativeCallable, "Function and callable member not found");
        // check function implementation in method
        if (!m_nativeCallable->getFunction()) {
            llvm::FunctionType* funcType = getFunctionType();
            m_func = llvm::Function::Create(
                funcType, llvm::GlobalValue::ExternalLinkage, "", m_module
            );
            m_nativeCallable->setFunction(m_func);

            // set argument name
            size_t j = 0;
            for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j) {
                ArgumentPtr arg = m_nativeCallable->getArgument(j);
                if (j) {
                    i->setName(arg->getName());
                } else {
                    i->setName("this");
                }
            }
        } else {
            m_func = m_nativeCallable->getFunction();
        }
    }
    if (m_func && m_nativeCallable)
        kiwi_assert(m_func->arg_size() == m_nativeCallable->size(), "Argument in function must be actual");
    return m_func;
}

llvm::Function* FunctionBuilder::createJITStartupPoint() {
    ObjectPtr self = dyn_cast<ObjectType>(m_nativeCallable->getOwnerType());
    if (!self) {
        BOOST_THROW_EXCEPTION(Exception()
            << exception_message("Self type must be Object type"));
    }

    /// create startup function
    llvm::FunctionType* startType = llvm::FunctionType::get(llvm::IntegerType::get(*m_context, 32), false);
    llvm::Function* startFunc     = llvm::dyn_cast<llvm::Function>(m_module->getOrInsertFunction("__start", startType));
    if (startFunc->empty()) {
        FunctionBuilder builder(self, startFunc);

        llvm::Function* func     = getFunction();
        llvm::FunctionType* type = func->getFunctionType();
        llvm::Type* returnType   = type->getReturnType();

        BlockBuilder block = builder.createBlock("start");

        // generate this
        ValueBuilder thisValue = block.createNew(self);

        // call main
        std::vector<ValueBuilder> args;
        args.push_back(thisValue);
        ValueBuilder result = thisValue.createCall(getNativeCallable(), args);
        if (returnType->isIntegerTy(32)) {
            llvm::ReturnInst::Create(*m_context, result.getValue(), block.getBlock());
        } else {
            llvm::APInt cst(32, 0, false);
            llvm::ConstantInt* zero = llvm::ConstantInt::get(*m_context, cst);
            llvm::ReturnInst::Create(*m_context, zero, block.getBlock());
        }
    }
    return startFunc;
}

BlockBuilder FunctionBuilder::createBlock(const Identifier& name) {
    kiwi_assert(getFunction(), "Function is not defined");
    llvm::BasicBlock* block = llvm::BasicBlock::Create(*m_context, name, getFunction());
    return BlockBuilder(*this, block);
}

//===--------------------------------------------------------------------------------------------------------------===//
//    Block builder methods
//===--------------------------------------------------------------------------------------------------------------===//
void BlockBuilder::createTrailReturn() {
    if (!m_block->getTerminator()) {
        llvm::Type* returnType = getFunctionType()->getReturnType();
        if (returnType->isVoidTy()) {
            llvm::ReturnInst::Create(*m_context, m_block);
        } else {
            llvm::Value* result = llvm::Constant::getNullValue(returnType);
            llvm::ReturnInst::Create(*m_context, result, m_block);
        }
    }
}

// Create void return
void BlockBuilder::createReturn() {
    /// @todo check equals of return type
    llvm::ReturnInst::Create(*m_context, m_block);
}

// Create return result of callable
void BlockBuilder::createReturn(ValueBuilder value) {
    llvm::ReturnInst::Create(*m_context, value.getValue(), m_block);
}

// Allocate memory in stack for mutable varaible
ValueBuilder BlockBuilder::createVariable(const Identifier& name, TypePtr type, bool autoInit) {
    llvm::Type* analog = type->getMetadata()->getBackendVariableType();
    llvm::AllocaInst* variable = new llvm::AllocaInst(analog, name, m_block);
    if (autoInit) {
        llvm::Value* null = llvm::Constant::getNullValue(type->getMetadata()->getBackendVariableType());
        new llvm::StoreInst(null, variable, m_block);
    }
    return ValueBuilder(*this, variable, type);
}

// Allocate memory in stack for mutable variable
ValueBuilder BlockBuilder::createThis() {
    TypePtr type         = getNativeOwner();
    llvm::Function* func = getFunction();
    kiwi_assert(!func->arg_empty(), "Function must have minimum one argument");

    ValueBuilder result(*this, func->arg_begin(), type);
    ThisConverter* converter = type->getMetadata()->getThisConverter();
    if (converter != 0) {
        return converter->emitFromThis(*this, result);
    }
    return result;
}

// Create store in mutable variable
ValueBuilder BlockBuilder::createStore(ValueBuilder variable, ValueBuilder value) {
    if (variable.getType() == value.getType()) {
        llvm::StoreInst* inst = new llvm::StoreInst(value.getValue(), variable.getValue(), m_block);
        return ValueBuilder(*this, value.getValue(), value.getType());
    }
    BOOST_THROW_EXCEPTION(Exception()
            << exception_message("Cast unknown"));
}

// Create load from mutable variable
ValueBuilder BlockBuilder::createLoad(ValueBuilder variable) {
    llvm::LoadInst* inst = new llvm::LoadInst(variable.getValue(), "", m_block);
    return ValueBuilder(*this, inst, variable.getType());
}

// Emit constants
ValueBuilder BlockBuilder::createIntConst(int32_t value) {
    llvm::ConstantInt* result = llvm::ConstantInt::get(*m_context, llvm::APInt(32, value, false));
    return ValueBuilder(*this, result, IntegerType::get32(getNativeContext()));
}

// Emit constants
ValueBuilder BlockBuilder::createBoolConst(bool value) {
    llvm::ConstantInt* result = llvm::ConstantInt::get(*m_context, llvm::APInt(1, value, false));
    return ValueBuilder(*this, result, BooleanType::get(getNativeContext()));
}

// Emit constants
ValueBuilder BlockBuilder::createCharConst(UChar value) {
    llvm::ConstantInt* result = llvm::ConstantInt::get(*m_context, llvm::APInt(16, value, true));
    return ValueBuilder(*this, result, CharType::get(getNativeContext()));
}

// Emit constants
ValueBuilder BlockBuilder::createStringConst(const String& value) {
    StringPtr type = StringType::get(getNativeContext());
    // get partial types for string
    llvm::Type* charType = llvm::IntegerType::get(*m_context, 16);
    llvm::Type* sizeType = llvm::IntegerType::get(*m_context, 32);
    llvm::ArrayType* bufferType = llvm::ArrayType::get(charType, value.length());

        // generate size
    llvm::Constant* size = llvm::ConstantInt::get(*m_context, llvm::APInt(32, value.length(), false));

    // generate buffer
    llvm::Constant* buffer = 0; {
        std::vector<llvm::Constant*> bufferConst;
        for (int i = 0; i < value.length(); ++i) {
            UChar c = value[i];
            llvm::Constant* value = llvm::ConstantInt::get(*m_context, llvm::APInt(16, c, false));
            bufferConst.push_back(value);
        }
        buffer = llvm::ConstantArray::get(bufferType, bufferConst);
    }

    // generate string type
    std::vector<llvm::Type*> elements;
    elements.push_back(sizeType);
    elements.push_back(bufferType);

    llvm::StructType* stringCstType = llvm::StructType::get(*m_context, elements);

    // generate string
    llvm::Constant* string = llvm::ConstantStruct::get(stringCstType, size, buffer, NULL);
    llvm::GlobalVariable* stringCst = new llvm::GlobalVariable(
        *m_module,
        stringCstType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        string,
        "string.cst"
     );
    stringCst->setUnnamedAddr(true); // Binary equal strings must be merged
    llvm::Type* stringType  = type->getMetadata()->getBackendVariableType();
    llvm::Value* result     = new llvm::BitCastInst(stringCst, stringType, "string.val", m_block);
    return ValueBuilder(*this, result, type);
}

// Create conditional goto
void BlockBuilder::createCond(ValueBuilder value, BlockBuilder blockTrue, BlockBuilder blockFalse) {
    llvm::Value* cond = value.getValue();
    if (!cond->getType()->isIntegerTy(1)) {
        BOOST_THROW_EXCEPTION(Exception()
            << exception_message("Condition must be boolean type"));
    }
    llvm::IRBuilder<>(m_block).CreateCondBr(cond, blockTrue.getBlock(), blockFalse.getBlock());
}

// Create unconditional goto
void BlockBuilder::createBr(BlockBuilder block) {
    llvm::IRBuilder<>(m_block).CreateBr(block.getBlock());
}

// Create new object
ValueBuilder BlockBuilder::createNew(ObjectPtr type, MethodPtr ctor, std::vector<ValueBuilder> cargs) {
    // get allocation function
    llvm::FunctionType* mallocType = llvm::FunctionType::get(llvm::IntegerType::get(*m_context, 8)->getPointerTo(), llvm::IntegerType::get(*m_context, 32), 0);
    llvm::Function* mallocFunc     = llvm::dyn_cast<llvm::Function>(m_module->getOrInsertFunction("kiwi_malloc", mallocType));

    // 1. sizeof data buffer
    TypeImpl* meta        = type->getMetadata();
    InheritanceInfo* info = meta->getOriginalMetadata();

    // 2. alloca data buffer
    llvm::Value* dataValue = 0;
    {
        llvm::Type* pointerType = llvm::IntegerType::get(*m_context, 8)->getPointerTo();
        std::vector<llvm::Type*> elements;
        elements.push_back(pointerType);
        llvm::Type* dataType = llvm::StructType::get(*m_context, llvm::makeArrayRef(elements), false)->getPointerTo();

        std::vector<llvm::Value*> args;
        args.push_back(makeConstantInt(*m_context, 1000));
        dataValue = llvm::CallInst::Create(mallocFunc, llvm::makeArrayRef(args), "", m_block);
        dataValue = new llvm::BitCastInst(dataValue, dataType, "type", m_block);
    }

    // 3. store pointer to type metadata
    {
        llvm::Value* tmeta = meta->getBackendPointer();    /// pointer to tmeta
        std::vector<llvm::Value*> bufferIdx;
        bufferIdx.push_back(makeConstantInt(*m_context, 0));
        bufferIdx.push_back(makeConstantInt(*m_context, 0));
        llvm::Value* tloc = llvm::GetElementPtrInst::CreateInBounds(dataValue, llvm::makeArrayRef(bufferIdx), "", m_block);
        new llvm::StoreInst(tmeta, tloc, "", m_block);
    }

    // 4. alloca object
    llvm::Value* object = 0;
    {
        std::vector<llvm::Value*> bufferIdx;
        llvm::Type* objectType = meta->getBackendThisType();
        llvm::Constant* null   = llvm::Constant::getNullValue(objectType);
        bufferIdx.push_back(makeConstantInt(*m_context, 1));
        llvm::Value* size = llvm::GetElementPtrInst::CreateInBounds(null, llvm::makeArrayRef(bufferIdx), "", m_block);
        size = new llvm::PtrToIntInst(size, llvm::IntegerType::get(*m_context, 32), "", m_block);

        std::vector<llvm::Value*> args;
        args.push_back(size);
        object = llvm::CallInst::Create(mallocFunc, llvm::makeArrayRef(args), "meta", m_block);
        object = new llvm::BitCastInst(object, objectType, "object", m_block);
    }

    // 5. Store pointer to vtable
    {
        llvm::Value* vtable = info->getVirtualTable().getBackendVariable();
        std::vector<llvm::Value*> bufferIdx;
        bufferIdx.push_back(makeConstantInt(*m_context, 0));
        bufferIdx.push_back(makeConstantInt(*m_context, 0));
        llvm::Value* vloc = llvm::GetElementPtrInst::CreateInBounds(object, llvm::makeArrayRef(bufferIdx), "", m_block);
        new llvm::StoreInst(vtable, vloc, "", m_block);
    }

    // 6. Store pointer to amap
    {
        llvm::Value* amap = info->getAddressMap().getBackendVariable();
        std::vector<llvm::Value*> bufferIdx;
        bufferIdx.push_back(makeConstantInt(*m_context, 0));
        bufferIdx.push_back(makeConstantInt(*m_context, 1));
        llvm::Value* aloc = llvm::GetElementPtrInst::CreateInBounds(object, llvm::makeArrayRef(bufferIdx), "", m_block);
        new llvm::StoreInst(amap, aloc, "", m_block);
    }

    // 7. Store data pointer to data
    {
        std::vector<llvm::Value*> bufferIdx;
        bufferIdx.push_back(makeConstantInt(*m_context, 0));
        bufferIdx.push_back(makeConstantInt(*m_context, 2));
        llvm::Value* dloc = llvm::GetElementPtrInst::CreateInBounds(object, llvm::makeArrayRef(bufferIdx), "", m_block);
        new llvm::StoreInst(dataValue, dloc, "", m_block);
    }
    return ValueBuilder(*this, object, type);
}

// Create store in object field
ValueBuilder BlockBuilder::createStore(ValueBuilder thisValue, FieldPtr field, ValueBuilder value) {
    llvm::Value* offset = offsetField(thisValue, field);
    new llvm::StoreInst(value.getValue(), offset, "", m_block);
    return ValueBuilder(*this, value.getValue(), field->getFieldType());
}

// Create load from object field
ValueBuilder BlockBuilder::createLoad(ValueBuilder thisValue, FieldPtr field) {
    llvm::Value* offset   = offsetField(thisValue, field);
    llvm::Value* loadInst = new llvm::LoadInst(offset, "", m_block);
    return ValueBuilder(*this, loadInst, field->getFieldType());
}

// Create call for callable with arguments
ValueBuilder BlockBuilder::createCall(MethodPtr call, std::vector<ValueBuilder> args) {
    MethodPolicy* policy = call->getPolicy();
    if (policy) {
        return policy->emit(*this, args);
    }
    BOOST_THROW_EXCEPTION(Exception() << exception_message("Function not implemented"));
}

// Returns pointer to value of field obkect
llvm::Value* BlockBuilder::offsetField(ValueBuilder thisValue, FieldPtr field) {
    llvm::Value* value    = thisValue.getValue();

    // load amap
    llvm::Value* amap = 0;
    {
        std::vector<llvm::Value*> addressIdx;
        addressIdx.push_back(makeConstantInt(*m_context, 0));
        addressIdx.push_back(makeConstantInt(*m_context, 1));
        llvm::Value* amapOffset = llvm::GetElementPtrInst::Create(value, makeArrayRef(addressIdx), "", m_block);
        amap = new llvm::LoadInst(amapOffset, "amap_ptr", m_block);

        // dereference amap
        amap = new llvm::LoadInst(amap, "amap", m_block);
    }

    // load data
    llvm::Value* data = 0;
    {
        std::vector<llvm::Value*> addressIdx;
        addressIdx.push_back(makeConstantInt(*m_context, 0));
        addressIdx.push_back(makeConstantInt(*m_context, 2));
        llvm::Value* dataOffset = llvm::GetElementPtrInst::Create(value, makeArrayRef(addressIdx), "", m_block);
        data = new llvm::LoadInst(dataOffset, "data", m_block);
    }

    // load offset
    llvm::Value* fieldOffset = 0;
    {
        std::vector<llvm::Value*> addressIdx;
        addressIdx.push_back(makeConstantInt(*m_context, 0));
        addressIdx.push_back(makeConstantInt(*m_context, field->getPosition()));
        llvm::Value* position = llvm::GetElementPtrInst::Create(amap, makeArrayRef(addressIdx), "position", m_block);
        fieldOffset = new llvm::LoadInst(position, "", m_block);
    }

    // calculate actual offset
    llvm::Value* castNull   = new llvm::PtrToIntInst(data, llvm::IntegerType::get(*m_context, 64), "", m_block);
    llvm::Value* castOffset = new llvm::ZExtInst(fieldOffset, llvm::IntegerType::get(*m_context, 64), "", m_block);
    llvm::Value* summInst   = llvm::BinaryOperator::Create(llvm::Instruction::Add, castNull, castOffset, "", m_block);

    /// @todo Add check for load instructions

    // cast to field type and return
    llvm::Type* fieldType = field->getFieldType()->getMetadata()->getBackendVariableType()->getPointerTo();
    llvm::Value* offset   = new llvm::IntToPtrInst(summInst, fieldType, "offset", m_block);

    // {
    //     llvm::Value* typeValue  = thisValue.getType()->getMetadata()->getBackendPointer();
    //     llvm::Type* pointerType = llvm::IntegerType::get(getContext(), 8)->getPointerTo();
    //     llvm::Function* dump_pointer = llvm::dyn_cast<llvm::Function>(getModule()->getOrInsertFunction("kiwi_dump_ptr", llvm::Type::getVoidTy(getContext()), pointerType, typeValue->getType(), NULL));
    //     std::vector<llvm::Value*> args;
    //     args.push_back(new llvm::IntToPtrInst(fieldOffset, pointerType, "", getBlock()));
    //     args.push_back(typeValue);
    //     llvm::Value* value = llvm::CallInst::Create(dump_pointer, makeArrayRef(args), "", getBlock());
    // }

    // {
    //     llvm::Value* typeValue  = thisValue.getType()->getMetadata()->getBackendPointer();
    //     llvm::Type* pointerType = llvm::IntegerType::get(getContext(), 8)->getPointerTo();
    //     llvm::Function* dump_pointer = llvm::dyn_cast<llvm::Function>(getModule()->getOrInsertFunction("kiwi_dump_ptr", llvm::Type::getVoidTy(getContext()), pointerType, typeValue->getType(), NULL));
    //     std::vector<llvm::Value*> args;
    //     args.push_back(new llvm::BitCastInst(data, pointerType, "", getBlock()));
    //     args.push_back(typeValue);
    //     llvm::Value* value = llvm::CallInst::Create(dump_pointer, makeArrayRef(args), "", getBlock());
    // }

    {
        llvm::Value* typeValue  = thisValue.getType()->getMetadata()->getBackendPointer();
        llvm::Type* pointerType = llvm::IntegerType::get(getContext(), 8)->getPointerTo();
        llvm::Function* dump_pointer = llvm::dyn_cast<llvm::Function>(getModule()->getOrInsertFunction("kiwi_dump_ptr", llvm::Type::getVoidTy(getContext()), pointerType, typeValue->getType(), NULL));
        std::vector<llvm::Value*> args;
        args.push_back(new llvm::BitCastInst(offset, pointerType, "", getBlock()));
        args.push_back(typeValue);
        llvm::Value* value = llvm::CallInst::Create(dump_pointer, makeArrayRef(args), "", getBlock());
    }

    return offset;
}
