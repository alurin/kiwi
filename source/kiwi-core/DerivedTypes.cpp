/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "TypeImpl.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Array.hpp"
#include "kiwi/Support/Cast.hpp"
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/ADT/ArrayRef.h>

#include <stack>

using namespace kiwi;
using namespace kiwi::codegen;

IntType::IntType(Module* module, int32_t size, bool unsign)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_meta->varType = llvm::IntegerType::get(context, size);
    m_typeID  = IntID;
    m_name    = "int";
}

BoolType::BoolType(Module* module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_meta->varType = llvm::IntegerType::get(context, 1);
    m_typeID  = BoolID;
    m_name    = "bool";
}

VoidType::VoidType(Module* module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_meta->varType = llvm::Type::getVoidTy(context);
    m_typeID  = VoidID;
    m_name    = "void";
}

CharType::CharType(Module* module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_meta->varType = llvm::IntegerType::get(context, 16);
    m_typeID  = CharID;
    m_name    = "char";
}

ObjectType::ObjectType(Module* module)
: Type(module) {
    m_typeID  = ObjectID;
    m_name    = "object";
}

StringType::StringType(Module* module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    llvm::Type* charType       = llvm::IntegerType::get(context, 16);
    llvm::Type* sizeType       = llvm::IntegerType::get(context, 32);
    llvm::Type* bufferType     = llvm::ArrayType::get(charType, 0);
    std::vector<llvm::Type*> elements;
    elements.push_back(sizeType);
    elements.push_back(bufferType);
    llvm::Type* stringType     = llvm::StructType::create(context, llvm::makeArrayRef(elements), "string", false);
    m_meta->varType          = stringType->getPointerTo(0);
    m_typeID                   = StringID;
}

IntType* IntType::create(Module* module, int32_t size, bool unsign) {
    IntType* type = new IntType(module, size, unsign);
    type->initializate();
    return type;
}

BoolType* BoolType::create(Module* module) {
    BoolType* type = new BoolType(module);
    type->initializate();
    return type;
}

VoidType* VoidType::create(Module* module) {
    VoidType* type = new VoidType(module);
    return type;
}

CharType* CharType::create(Module* module) {
    CharType* type = new CharType(module);
    type->initializate();
    return type;
}

StringType* StringType::create(Module* module) {
    StringType* type = new StringType(module);
    type->initializate();
    return type;
}

ObjectType* ObjectType::create(Module* module) {
    ObjectType* type = new ObjectType(module);
    return type;
}

ObjectType* ObjectType::create(Module* module, const Identifier& name) {
    ObjectType* type = new ObjectType(module);
    type->m_name = name;
    module->registerType(type, name);
    return type;
}

void IntType::initializate() {
    Context* context = m_module->getContext();
    Type* boolTy = BoolType::get(context);
    Type* voidTy = VoidType::get(context);
    Type* intTy = this;

    addUnary(Member::Pos,  intTy)->setPolicy(new LlvmZeroUnaryOperator(llvm::Instruction::Add, intTy));
    addUnary(Member::Neg,  intTy)->setPolicy(new LlvmZeroUnaryOperator(llvm::Instruction::Sub, intTy));

    addBinary(Member::Add, intTy, intTy)->setPolicy(new LlvmBinaryOperator(llvm::Instruction::Add, intTy));
    addBinary(Member::Sub, intTy, intTy)->setPolicy(new LlvmBinaryOperator(llvm::Instruction::Sub, intTy));
    addBinary(Member::Mul, intTy, intTy)->setPolicy(new LlvmBinaryOperator(llvm::Instruction::Mul, intTy));

    addBinary(Member::Eq,  boolTy, intTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    addBinary(Member::Neq, boolTy, intTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_NE, context));
    addBinary(Member::Gt,  boolTy, intTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_SGT, context));
    addBinary(Member::Ge,  boolTy, intTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_SGE, context));
    addBinary(Member::Le,  boolTy, intTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_SLT, context));
    addBinary(Member::Lt,  boolTy, intTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_SLE, context));

    addUnary(Member::Print, voidTy)->setPolicy(new LlvmIntegerPrintOperator());
}

void BoolType::initializate() {
    Context* context = m_module->getContext();
    Type*     voidTy = VoidType::get(context);
    Type*     boolTy = this;

    addBinary(Member::Eq,  boolTy, boolTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    addBinary(Member::Neq, boolTy, boolTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_NE, context));

    addUnary(Member::Print, voidTy)->setPolicy(new LlvmBoolPrintOperator());
}

void CharType::initializate() {
    Context* context = m_module->getContext();
    Type*     boolTy = BoolType::get(context);
    Type*     voidTy = VoidType::get(context);
    Type*     charTy = this;

    addUnary(Member::Print, voidTy)->setPolicy(new LlvmCharPrintOperator());
}

void StringType::initializate() {
    Context* context = m_module->getContext();
    Type*     charTy = CharType::get(context);
    Type*     boolTy = BoolType::get(context);
    Type*     voidTy = VoidType::get(context);
    Type*      intTy = IntType::get32(context);
    Type*   stringTy = this;

    addBinary(Member::Eq,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    addBinary(Member::Neq, boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_NE, context));
    addBinary(Member::Gt,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SGT, context));
    addBinary(Member::Ge,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SGE, context));
    addBinary(Member::Le,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SLT, context));
    addBinary(Member::Lt,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SLE, context));


    // add(Member::Add,         stringTy, stringTy,                    new LlvmStringConcatenate()); // a + b
    addMultiary(Member::Subtraction, charTy,   makeVector(intTy, 0))->setPolicy(new LlvmStringSubtraction()); // [a]
    addMultiary(Member::Subtraction, stringTy, makeVector(intTy, intTy, 0))->setPolicy(new LlvmStringSubtraction()); // [a, b]

    addUnary(Member::Print, voidTy)->setPolicy(new LlvmStringPrintOperator());
}

IntType* IntType::get32(Context* context) {
    ContextImpl* meta = context->getMetadata();
    return meta->int32Ty;
}

BoolType* BoolType::get(Context* context) {
    ContextImpl* meta = context->getMetadata();
    return meta->boolTy;
}

VoidType* VoidType::get(Context* context) {
    ContextImpl* meta = context->getMetadata();
    return meta->voidTy;
}

CharType* CharType::get(Context* context) {
    ContextImpl* meta = context->getMetadata();
    return meta->charTy;
}

StringType* StringType::get(Context* context) {
    ContextImpl* meta = context->getMetadata();
    return meta->stringTy;
}

/// add parent type
bool ObjectType::inherit(ObjectType* type) {
    m_meta->insertBase(type);
}

/// inherit type?
bool ObjectType::isInherit(const ObjectType* type) const{
    return m_meta->isBase(type);
}

// /// implement interface?
// bool ObjectType::isImplement(const InterfaceType* type, bool duckCast) const {
//     if (duckCast) {
//         m_meta->implement(type, true);
//     }
//     return m_meta->isBase(type);
// }

// Emit type structure
void ObjectType::emit() {
    if (m_meta->varType != 0) {
        return;
    }

    // collect fields
    llvm::LLVMContext& context = m_module->getContext()->getContext();
    llvm::Module* module       = m_module->getModule();
    std::vector<llvm::Type*> types;

    // add vtable and vmap to type
    llvm::Type* sizeType            = llvm::IntegerType::get(context, 32);
    llvm::ArrayType* addressMapType = llvm::ArrayType::get(sizeType, 0); //m_fields.size());
    types.push_back(addressMapType->getPointerTo());

    // add field to type
    int j = 0;
    for (MemberSet<Field>::const_iterator i = m_meta->fields().begin(); i != m_meta->fields().end(); ++i, ++j) {
        Field* field = *i;

        Type* type = field->getFieldType();
        types.push_back(type->getVarType());

        field->setPosition(j);
    }

    // emit llvm type analog
    llvm::StructType* type = 0;
    if (types.size()) {
        type = llvm::StructType::create(types);
    } else {
        type = llvm::StructType::create(context);
    }
    m_meta->varType = type->getPointerTo();

    // emit address map
    std::vector<llvm::Constant*> addresses;
    std::vector<llvm::Constant*> buffer;
    llvm::Constant* nullCst = llvm::Constant::getNullValue(m_meta->varType);
    llvm::ConstantInt* zero = llvm::ConstantInt::get(context, llvm::APInt(32, 0, false));
    j = 0;
    for (MemberSet<Field>::const_iterator i = m_meta->fields().begin(); i != m_meta->fields().end(); ++i, ++j) {
        // create variable for compare
        llvm::APInt idxV(32, j + 1, false);
        llvm::ConstantInt* idx = llvm::ConstantInt::get(context, idxV);

        // buffer
        buffer.clear();
        buffer.push_back(zero);
        buffer.push_back(idx);

        llvm::Constant* cst = llvm::ConstantExpr::getGetElementPtr(nullCst, makeArrayRef(buffer));
        addresses.push_back(cst);
    }

    llvm::Constant* addressMapValue = llvm::ConstantArray::get(addressMapType, makeArrayRef(addresses));

    // generate string
    m_meta->addressMap  = new llvm::GlobalVariable(
        *module,
        addressMapType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        addressMapValue,
        "amap"
    );

    // add simple constructor
    std::vector<Type*> empty;
    addMultiary(Member::Constructor, VoidType::get(m_module->getContext()), empty)->setPolicy(new LlvmCtorEmitter());
}


/// return LLVM analog for address map
llvm::GlobalVariable* ObjectType::getVarAddressMap() const {
    return m_meta->addressMap;
}

/// return LLVM analog for address map
llvm::GlobalVariable* ObjectType::getVarVirtualTable() const {
    return m_meta->virtualTable;
}
