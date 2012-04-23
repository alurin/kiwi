#include "ContextImpl.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Members.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>
#include <llvm/ADT/ArrayRef.h>

using namespace kiwi;
using namespace kiwi::codegen;

IntType::IntType(Module* module, int32_t size, bool unsign)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::IntegerType::get(context, size);
    m_typeID  = IntID;
}

BoolType::BoolType(Module* module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::IntegerType::get(context, 1);
    m_typeID  = BoolID;
}

VoidType::VoidType(Module* module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::Type::getVoidTy(context);
    m_typeID  = VoidID;
}

CharType::CharType(Module* module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::IntegerType::get(context, 16);
    m_typeID  = CharID;
}

ObjectType::ObjectType(Module* module)
: Type(module), m_addressMap(0), m_virtualTable(0) {
    m_typeID  = ObjectID;
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
    m_varType                  = stringType->getPointerTo(0);
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
    return type;
}

void IntType::initializate() {
    Context* context = m_module->getContext();
    Type* boolTy = BoolType::get(context);
    Type* voidTy = VoidType::get(context);
    Type* intTy = this;

    add(UnaryOperator::POS,  intTy,         new LlvmZeroUnaryOperator(llvm::Instruction::Add, intTy));
    add(UnaryOperator::NEG,  intTy,         new LlvmZeroUnaryOperator(llvm::Instruction::Sub, intTy));

    add(BinaryOperator::ADD, intTy, intTy,  new LlvmBinaryOperator(llvm::Instruction::Add, intTy));
    add(BinaryOperator::SUB, intTy, intTy,  new LlvmBinaryOperator(llvm::Instruction::Sub, intTy));
    add(BinaryOperator::MUL, intTy, intTy,  new LlvmBinaryOperator(llvm::Instruction::Mul, intTy));

    add(BinaryOperator::EQ,  boolTy, intTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    add(BinaryOperator::NEQ, boolTy, intTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_NE, context));
    add(BinaryOperator::GT,  boolTy, intTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_SGT, context));
    add(BinaryOperator::GE,  boolTy, intTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_SGE, context));
    add(BinaryOperator::LE,  boolTy, intTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_SLT, context));
    add(BinaryOperator::LT,  boolTy, intTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_SLE, context));

    add(UnaryOperator::PRINT, voidTy, new LlvmIntegerPrintOperator());
}

void BoolType::initializate() {
    Context* context = m_module->getContext();
    Type*     voidTy = VoidType::get(context);
    Type*     boolTy = this;

    add(BinaryOperator::EQ,  boolTy, boolTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    add(BinaryOperator::NEQ, boolTy, boolTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_NE, context));

    add(UnaryOperator::PRINT, voidTy, new LlvmBoolPrintOperator());
}

void CharType::initializate() {
    Context* context = m_module->getContext();
    Type*     boolTy = BoolType::get(context);
    Type*     voidTy = VoidType::get(context);
    Type*     charTy = this;

    add(UnaryOperator::PRINT, voidTy, new LlvmCharPrintOperator());
}

void StringType::initializate() {
    Context* context = m_module->getContext();
    Type*     charTy = CharType::get(context);
    Type*     boolTy = BoolType::get(context);
    Type*     voidTy = VoidType::get(context);
    Type*   stringTy = this;

    add(BinaryOperator::EQ,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    add(BinaryOperator::NEQ, boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_NE, context));
    add(BinaryOperator::GT,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SGT, context));
    add(BinaryOperator::GE,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SGE, context));
    add(BinaryOperator::LE,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SLT, context));
    add(BinaryOperator::LT,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SLE, context));

    add(UnaryOperator::PRINT, voidTy, new LlvmStringPrintOperator());
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

// Emit type structure
void ObjectType::emit() {
    if (m_varType != 0) {
        return;
    }

    // collect fields
    std::vector<llvm::Type*> types;
    int j = 0;
    for (std::vector<Field*>::iterator i = m_fields.begin(); i != m_fields.end(); ++i, ++j) {
        Field* field = *i;

        Type* type = field->getFieldType();
        types.push_back(type->getVarType());

        field->setPosition(j);
    }

    // emit llvm type analog
    llvm::LLVMContext& context = m_module->getContext()->getContext();
    llvm::Module* module       = m_module->getModule();
    if (types.size()) {
        m_varType = llvm::StructType::create(types);
    } else {
        m_varType = llvm::StructType::create(context);
    }

    // emit address map
    std::vector<llvm::Constant*> addresses;
    std::vector<llvm::Constant*> buffer;
    llvm::Constant* nullCst = llvm::Constant::getNullValue(m_varType->getPointerTo());
    llvm::ConstantInt* zero = llvm::ConstantInt::get(context, llvm::APInt(32, 0, false));
    j = 0;
    for (std::vector<Field*>::iterator i = m_fields.begin(); i != m_fields.end(); ++i, ++j) {
        // create variable for compare
        llvm::APInt idxV(32, j, false);
        llvm::ConstantInt* idx = llvm::ConstantInt::get(context, idxV);

        // buffer
        buffer.clear();
        buffer.push_back(zero);
        buffer.push_back(idx);

        llvm::Constant* cst = llvm::ConstantExpr::getGetElementPtr(nullCst, makeArrayRef(buffer));
        addresses.push_back(cst);
    }

    llvm::Type* sizeType            = llvm::IntegerType::get(context, 8)->getPointerTo();
    llvm::ArrayType* addressMapType = llvm::ArrayType::get(sizeType, m_fields.size());
    llvm::Constant* addressMapValue = llvm::ConstantArray::get(addressMapType, makeArrayRef(addresses));

    // generate string
    m_addressMap  = new llvm::GlobalVariable(
        *module,
        addressMapType,
        true,
        llvm::GlobalValue::PrivateLinkage,
        addressMapValue,
        "amap"
    );
}
