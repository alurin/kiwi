#include "ContextMeta.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Members.hpp"
#include "codegen/LlvmEmitter.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>
#include <llvm/ADT/ArrayRef.h>

using namespace kiwi;
using namespace kiwi::codegen;

IntType::IntType(ModuleRef module, int32_t size, bool unsign)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::IntegerType::get(context, size);
}

BoolType::BoolType(ModuleRef module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::IntegerType::get(context, 1);
}

VoidType::VoidType(ModuleRef module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::Type::getVoidTy(context);
}

CharType::CharType(ModuleRef module)
: Type(module) {
    llvm::LLVMContext& context = module->getContext()->getContext();
    m_varType = llvm::IntegerType::get(context, 16);
}

StringType::StringType(ModuleRef module)
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
}

IntTy IntType::create(ModuleRef module, int32_t size, bool unsign)
{
    IntTy type = IntTy(new IntType(module, size, unsign));
    type->initializate();
    return type;
}

BoolTy BoolType::create(ModuleRef module)
{
    BoolTy type = BoolTy(new BoolType(module));
    type->initializate();
    return type;
}

VoidTy VoidType::create(ModuleRef module)
{
    VoidTy type = VoidTy(new VoidType(module));
    return type;
}

CharTy CharType::create(ModuleRef module)
{
    CharTy type = CharTy(new CharType(module));
    type->initializate();
    return type;
}

StringTy StringType::create(ModuleRef module)
{
    StringTy type = StringTy(new StringType(module));
    type->initializate();
    return type;
}

void IntType::initializate()
{
    ContextRef context = m_module.lock()->getContext();
    TypeRef     boolTy = BoolType::get(context);
    TypeRef     voidTy = VoidType::get(context);
    TypeRef     intTy  = shared_from_this();

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

void BoolType::initializate()
{
    ContextRef context = m_module.lock()->getContext();
    TypeRef     voidTy = VoidType::get(context);
    TypeRef     boolTy = shared_from_this();

    add(BinaryOperator::EQ,  boolTy, boolTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    add(BinaryOperator::NEQ, boolTy, boolTy, new LlvmIntegerCompareOperator(llvm::CmpInst::ICMP_NE, context));

    add(UnaryOperator::PRINT, voidTy, new LlvmBoolPrintOperator());
}


void CharType::initializate()
{
    ContextRef context = m_module.lock()->getContext();
    TypeRef     boolTy = BoolType::get(context);
    TypeRef     voidTy = VoidType::get(context);
    TypeRef     charTy = shared_from_this();

    add(UnaryOperator::PRINT, voidTy, new LlvmCharPrintOperator());
}

void StringType::initializate()
{
    ContextRef context = m_module.lock()->getContext();
    TypeRef     charTy = CharType::get(context);
    TypeRef     boolTy = BoolType::get(context);
    TypeRef     voidTy = VoidType::get(context);
    TypeRef   stringTy = shared_from_this();

    add(BinaryOperator::EQ,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_EQ, context));
    add(BinaryOperator::NEQ, boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_NE, context));
    add(BinaryOperator::GT,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SGT, context));
    add(BinaryOperator::GE,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SGE, context));
    add(BinaryOperator::LE,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SLT, context));
    add(BinaryOperator::LT,  boolTy, stringTy, new LlvmStringCompareOperator(llvm::CmpInst::ICMP_SLE, context));

    add(UnaryOperator::PRINT, voidTy, new LlvmStringPrintOperator());
}

IntTy IntType::get32(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->int32Ty;
}

BoolTy BoolType::get(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->boolTy;
}

VoidTy VoidType::get(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->voidTy;
}

CharTy CharType::get(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->charTy;
}

StringTy StringType::get(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->stringTy;
}