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

// /// implement interface?
// bool ObjectType::isImplement(const InterfaceTypePtr type, bool duckCast) const {
//     if (duckCast) {
//         m_meta->implement(type, true);
//     }
//     return m_meta->isBase(type);
// }

// Emit type structure
void ObjectType::emit() {
    if (m_meta->getBackendVariableType() != 0) {
        return;
    }

    // collect fields
    llvm::LLVMContext& context  = getContext()->getMetadata()->getBackendContext();
    llvm::Module* module        = getModule()->getMetadata()->getBackendModule();

    llvm::Type* pointerType     = llvm::IntegerType::get(context, 8)->getPointerTo();
    llvm::Type* vtable          = llvm::ArrayType::get(pointerType, 0);

    llvm::Type* offsetType      = llvm::IntegerType::get(context, 32);
    llvm::Type* amap            = llvm::ArrayType::get(offsetType, 0);

    llvm::Type* dataType        = pointerType; // it pointers

    llvm::Type* vmeta           = vtable->getPointerTo();
    llvm::Type* ameta           = vtable->getPointerTo();

    std::vector<llvm::Type*> types;

    /// storage type
    types.push_back(pointerType);
    types.push_back(dataType);
    llvm::Type* storageType     = llvm::StructType::create(types)->getPointerTo();

    /// variable type
    types.clear();
    types.push_back(vmeta);
    types.push_back(ameta);
    types.push_back(storageType);
    llvm::Type* varType         = llvm::StructType::create(types);

    /// store types
    m_meta->setBackendVariableType(varType);
    m_meta->setBackendThisType(storageType);
    m_meta->setThisConverter(new ObjectThisConverter());

    // std::vector<llvm::Type*> types;

    // // // add vtable to type
    // // llvm::Type* pointerType           = llvm::IntegerType::get(context, 8)->getPointerTo();
    // // llvm::ArrayType* virtualTableType = llvm::ArrayType::get(pointerType, m_meta->methods().size());
    // // llvm::ArrayType* virtualTableSamp = llvm::ArrayType::get(pointerType, 0);
    // // types.push_back(virtualTableType);

    // // add amap to type
    // llvm::Type* sizeType            = llvm::IntegerType::get(context, 32);
    // llvm::ArrayType* addressMapType = llvm::ArrayType::get(sizeType, m_meta->fields().size());
    // llvm::ArrayType* addressMapSamp = llvm::ArrayType::get(sizeType, 0);
    // types.push_back(addressMapType);

    // // add field to type
    // int j = 0;
    // for (MemberSet<Field>::const_iterator i = m_meta->fields().begin(); i != m_meta->fields().end(); ++i, ++j) {
    //     FieldPtr field = *i;

    //     TypePtr type = field->getFieldType();
    //     types.push_back(type->getVarType());

    //     field->setPosition(j);
    // }

    // // emit llvm type analog
    // llvm::StructType* type = 0;
    // if (types.size()) {
    //     type = llvm::StructType::create(types);
    // } else {
    //     type = llvm::StructType::create(context);
    // }
    // m_meta->varType = type->getPointerTo();

    // {
    //     // emit address map
    //     std::vector<llvm::Constant*> addresses;
    //     std::vector<llvm::Constant*> buffer;
    //     llvm::Constant* nullCst = llvm::Constant::getNullValue(m_meta->varType);
    //     llvm::ConstantInt* zero = llvm::ConstantInt::get(context, llvm::APInt(32, 0, false));
    //     j = 1;
    //     for (MemberSet<Field>::const_iterator i = m_meta->fields().begin(); i != m_meta->fields().end(); ++i, ++j) {
    //         // create variable for compare
    //         llvm::APInt idxV(32, j, false);
    //         llvm::ConstantInt* idx = llvm::ConstantInt::get(context, idxV);

    //         // buffer
    //         buffer.clear();
    //         buffer.push_back(zero);
    //         buffer.push_back(idx);

    //         llvm::Constant* cst = llvm::ConstantExpr::getGetElementPtr(nullCst, makeArrayRef(buffer));
    //         addresses.push_back(cst);
    //     }

    //     llvm::Constant* addressMapValue = llvm::ConstantArray::get(addressMapType, makeArrayRef(addresses));

    //     // generate string
    //     m_meta->addressMap  = new llvm::GlobalVariable(
    //         *module,
    //         addressMapType,
    //         true,
    //         llvm::GlobalValue::PrivateLinkage,
    //         addressMapValue,
    //         "amap"
    //     );
    // }
    // // add simple constructor
    // std::vector<TypePtr> empty;
    // addMultiary(Member::Constructor, VoidType::get(m_module.lock()->getContext()), empty)->setPolicy(new LlvmCtorEmitter());
}
