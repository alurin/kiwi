#include "ContextMeta.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "codegen/LlvmEmitter.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>
#include <llvm/ADT/ArrayRef.h>

using namespace kiwi;
using namespace kiwi::codegen;

typedef boost::shared_ptr<IntType>    IntTypeRef;
typedef boost::shared_ptr<BoolType>   BoolTypeRef;
typedef boost::shared_ptr<VoidType>   VoidTypeRef;
typedef boost::shared_ptr<CharType>   CharTypeRef;
typedef boost::shared_ptr<StringType> StringTypeRef;

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
    llvm::Type* stringType     = llvm::StructType::create(llvm::makeArrayRef(elements));
    m_varType                  = stringType->getPointerTo(0);
}

TypeRef IntType::create(ModuleRef module, int32_t size, bool unsign)
{
    IntTypeRef type = IntTypeRef(new IntType(module, size, unsign));
    type->initializate();
    return type;
}

TypeRef BoolType::create(ModuleRef module)
{
    BoolTypeRef type = BoolTypeRef(new BoolType(module));
    type->initializate();
    return type;
}

TypeRef VoidType::create(ModuleRef module)
{
    VoidTypeRef type = VoidTypeRef(new VoidType(module));
    return type;
}

TypeRef CharType::create(ModuleRef module)
{
    CharTypeRef type = CharTypeRef(new CharType(module));
    type->initializate();
    return type;
}

TypeRef StringType::create(ModuleRef module)
{
    StringTypeRef type = StringTypeRef(new StringType(module));
    type->initializate();
    return type;
}

void IntType::initializate()
{
    ContextRef context = m_module.lock()->getContext();
    TypeRef     intTy  = shared_from_this();
    TypeRef     boolTy = BoolType::get(context);

    add(UnaryOperator::POS,  intTy,         new LlvmZeroUnaryOperator(llvm::Instruction::Add, intTy));
    add(UnaryOperator::NEG,  intTy,         new LlvmZeroUnaryOperator(llvm::Instruction::Sub, intTy));

    add(BinaryOperator::ADD, intTy, intTy,  new LlvmBinaryOperator(llvm::Instruction::Add, intTy));
    add(BinaryOperator::SUB, intTy, intTy,  new LlvmBinaryOperator(llvm::Instruction::Sub, intTy));
    add(BinaryOperator::MUL, intTy, intTy,  new LlvmBinaryOperator(llvm::Instruction::Mul, intTy));

    add(BinaryOperator::EQ,  boolTy, intTy, new LlvmICompareOperator(llvm::CmpInst::ICMP_EQ, context));
    add(BinaryOperator::NEQ, boolTy, intTy, new LlvmICompareOperator(llvm::CmpInst::ICMP_NE, context));
    add(BinaryOperator::GT,  boolTy, intTy, new LlvmICompareOperator(llvm::CmpInst::ICMP_SGT, context));
    add(BinaryOperator::GE,  boolTy, intTy, new LlvmICompareOperator(llvm::CmpInst::ICMP_SGE, context));
    add(BinaryOperator::LE,  boolTy, intTy, new LlvmICompareOperator(llvm::CmpInst::ICMP_SLT, context));
    add(BinaryOperator::LT,  boolTy, intTy, new LlvmICompareOperator(llvm::CmpInst::ICMP_SLE, context));
}

void BoolType::initializate()
{
    ContextRef context = m_module.lock()->getContext();
    TypeRef     boolTy = shared_from_this();

    add(BinaryOperator::EQ,  boolTy, boolTy, new LlvmICompareOperator(llvm::CmpInst::ICMP_EQ, context));
    add(BinaryOperator::NEQ, boolTy, boolTy, new LlvmICompareOperator(llvm::CmpInst::ICMP_NE, context));
}


void CharType::initializate()
{ }
void StringType::initializate()
{ }

TypeRef IntType::get32(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->int32Ty;
}

TypeRef BoolType::get(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->boolTy;
}

TypeRef VoidType::get(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->voidTy;
}

TypeRef CharType::get(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->charTy;
}

TypeRef StringType::get(ContextRef context)
{
    ContextMeta* meta = context->getMetadata();
    return meta->stringTy;
}