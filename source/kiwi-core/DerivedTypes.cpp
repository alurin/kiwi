/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "TypeImpl.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Cast.hpp"
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/ADT/ArrayRef.h>

#include <stack>

using namespace kiwi;
using namespace kiwi::codegen;

IntegerType::IntegerType(ModulePtr module, int32_t size, bool unsign)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getMetadata()->getBackendContext();
    m_typeID  = IntID;
    m_name    = "int";
    m_meta->setBackendVariableType(llvm::IntegerType::get(context, size));
}

BooleanType::BooleanType(ModulePtr module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getMetadata()->getBackendContext();
    m_typeID  = BoolID;
    m_name    = "bool";
    m_meta->setBackendVariableType(llvm::IntegerType::get(context, 1));
}

VoidType::VoidType(ModulePtr module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getMetadata()->getBackendContext();
    m_typeID  = VoidID;
    m_name    = "void";
    m_meta->setBackendVariableType(llvm::Type::getVoidTy(context));
}

CharType::CharType(ModulePtr module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getMetadata()->getBackendContext();
    m_typeID  = CharID;
    m_name    = "char";
    m_meta->setBackendVariableType(llvm::IntegerType::get(context, 16));
}

ObjectType::ObjectType(ModulePtr module)
: Type(module) {
    m_typeID  = ObjectID;
    m_name    = "object";
        // collect fields
    llvm::LLVMContext& context  = getContext()->getMetadata()->getBackendContext();

    llvm::Type* pointerType     = llvm::IntegerType::get(context, 8)->getPointerTo();
    llvm::Type* vtable          = llvm::ArrayType::get(pointerType, 0);

    llvm::Type* offsetType      = llvm::IntegerType::get(context, 32);
    llvm::Type* amap            = llvm::ArrayType::get(offsetType, 0);

    llvm::Type* vmeta           = vtable->getPointerTo()->getPointerTo();
    llvm::Type* ameta           = amap->getPointerTo()->getPointerTo();

    std::vector<llvm::Type*> elements;
    elements.push_back(pointerType);
    llvm::Type* dataType = llvm::StructType::get(context, llvm::makeArrayRef(elements))->getPointerTo();

    // storage type
    std::vector<llvm::Type*> types;
    types.push_back(vmeta);
    types.push_back(ameta);
    types.push_back(dataType);
    llvm::Type* varType = llvm::StructType::get(context, types)->getPointerTo();

    // store types
    m_meta->setBackendVariableType(varType);
}

StringType::StringType(ModulePtr module)
: Type(module) {
    m_typeID                   = StringID;
    llvm::LLVMContext& context = module->getContext()->getMetadata()->getBackendContext();
    llvm::Type* charType       = llvm::IntegerType::get(context, 16);
    llvm::Type* sizeType       = llvm::IntegerType::get(context, 32);
    llvm::Type* bufferType     = llvm::ArrayType::get(charType, 0);
    std::vector<llvm::Type*> elements;
    elements.push_back(sizeType);
    elements.push_back(bufferType);
    llvm::Type* stringType     = llvm::StructType::create(context, llvm::makeArrayRef(elements), "string", false);
    m_meta->setBackendVariableType(stringType->getPointerTo(0));
}

IntegerPtr IntegerType::create(ModulePtr module, int32_t size, bool unsign) {
    IntegerPtr type = IntegerPtr(new IntegerType(module, size, unsign));
    type->initializate();
    return type;
}

BooleanPtr BooleanType::create(ModulePtr module) {
    BooleanPtr type = BooleanPtr(new BooleanType(module));
    type->initializate();
    return type;
}

VoidPtr VoidType::create(ModulePtr module) {
    VoidPtr type = VoidPtr(new VoidType(module));
    return type;
}

CharPtr CharType::create(ModulePtr module) {
    CharPtr type = CharPtr(new CharType(module));
    type->initializate();
    return type;
}

StringPtr StringType::create(ModulePtr module) {
    StringPtr type = StringPtr(new StringType(module));
    type->initializate();
    return type;
}

ObjectPtr ObjectType::create(ModulePtr module) {
    ObjectPtr type = ObjectPtr(new ObjectType(module));
    module->getMetadata()->registerType(type);
    return type;
}

ObjectPtr ObjectType::create(ModulePtr module, const Identifier& name) {
    ObjectPtr type = ObjectPtr(new ObjectType(module));
    type->m_name = name;
    type->m_meta->getBackendPointer()->setName(name + "::_type");
    module->getMetadata()->registerType(type, name);
    return type;
}

void IntegerType::initializate() {
    ContextPtr context = getContext();
    TypePtr boolTy = BooleanType::get(context);
    TypePtr voidTy = VoidType::get(context);
    TypePtr intTy = shared_from_this();

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

void BooleanType::initializate() {
    ContextPtr context = getContext();
    TypePtr     voidTy = VoidType::get(context);
    TypePtr     boolTy = shared_from_this();

    addBinary(Member::Eq,  boolTy, boolTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    addBinary(Member::Neq, boolTy, boolTy)->setPolicy(new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_NE, context));

    addUnary(Member::Print, voidTy)->setPolicy(new LlvmBoolPrintOperator());
}

void CharType::initializate() {
    ContextPtr context = getContext();
    TypePtr     boolTy = BooleanType::get(context);
    TypePtr     voidTy = VoidType::get(context);
    TypePtr     charTy = shared_from_this();

    addUnary(Member::Print, voidTy)->setPolicy(new LlvmCharPrintOperator());
}

void StringType::initializate() {
    ContextPtr context = getContext();
    TypePtr     charTy = CharType::get(context);
    TypePtr     boolTy = BooleanType::get(context);
    TypePtr     voidTy = VoidType::get(context);
    TypePtr      intTy = IntegerType::get32(context);
    TypePtr   stringTy = shared_from_this();

    addBinary(Member::Eq,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    addBinary(Member::Neq, boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_NE, context));
    addBinary(Member::Gt,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SGT, context));
    addBinary(Member::Ge,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SGE, context));
    addBinary(Member::Le,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SLT, context));
    addBinary(Member::Lt,  boolTy, stringTy)->setPolicy(new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SLE, context));

    std::vector<TypePtr> types;
    types.push_back(intTy);
    addMultiary(Member::Subtraction, charTy, types)->setPolicy(new LlvmStringSubtraction()); // [a]

    types.clear();
    types.push_back(intTy);
    types.push_back(intTy);
    addMultiary(Member::Subtraction, stringTy, types)->setPolicy(new LlvmStringSubtraction()); // [a, b]

    addUnary(Member::Print, voidTy)->setPolicy(new LlvmStringPrintOperator());
}

IntegerPtr IntegerType::get32(ContextPtr context) {
    ContextImpl* meta = context->getMetadata();
    return meta->int32Ty;
}

BooleanPtr BooleanType::get(ContextPtr context) {
    ContextImpl* meta = context->getMetadata();
    return meta->boolTy;
}

VoidPtr VoidType::get(ContextPtr context) {
    ContextImpl* meta = context->getMetadata();
    return meta->voidTy;
}

CharPtr CharType::get(ContextPtr context) {
    ContextImpl* meta = context->getMetadata();
    return meta->charTy;
}

StringPtr StringType::get(ContextPtr context) {
    ContextImpl* meta = context->getMetadata();
    return meta->stringTy;
}

/// add parent type
bool ObjectType::inherit(ObjectPtr type) {
    m_meta->insertBase(type);
}

/// inherit type?
bool ObjectType::isInherit(const ObjectPtr type) const{
    return m_meta->isBase(type);
}

// Emit type structure
void ObjectType::update() {
    m_meta->setThisConverter(new UpcastConverter(ObjectPtr(shared_from_this(), this)));
}
