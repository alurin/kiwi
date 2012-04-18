#include "ContextMeta.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "codegen/LlvmEmitter.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>


using namespace kiwi;
using namespace kiwi::codegen;

typedef boost::shared_ptr<IntType>  IntTypeRef;
typedef boost::shared_ptr<BoolType> BoolTypeRef;

Type::Type(ModuleRef module)
: m_module(module), m_varType(0) { }

Type::~Type() { }

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

// constructor
UnaryOperator::UnaryOperator(
    UnaryOperator::Opcode opcode,
    TypeRef resultType,
    codegen::UnaryEmitter* emitter
) : m_opcode(opcode), m_resultType(resultType), m_emitter(emitter)
{ }

// constructor
BinaryOperator::BinaryOperator(
    BinaryOperator::Opcode opcode,
    TypeRef resultType,
    TypeRef operatorType,
    codegen::BinaryEmitter* emitter
) : m_opcode(opcode), m_resultType(resultType), m_operatorType(operatorType), m_emitter(emitter)
{ }

// add binary operator
UnaryRef Type::add(
    UnaryOperator::Opcode opcode,
    TypeRef resultType,
    codegen::UnaryEmitter* emitter
) {
    UnaryRef op = UnaryRef(new UnaryOperator(opcode, resultType, emitter));
    m_unary.push_back(op);
    return op;
}

// add binary operator
BinaryRef Type::add(
    BinaryOperator::Opcode opcode,
    TypeRef resultType,
    TypeRef operatorType,
    codegen::BinaryEmitter* emitter
) {
    BinaryRef op = BinaryRef(new BinaryOperator(opcode, resultType, operatorType, emitter));
    m_binary.push_back(op);
    return op;
}

// find unary operator
UnaryRef Type::find(UnaryOperator::Opcode opcode)
{
    for (std::vector<UnaryRef>::iterator i = m_unary.begin(); i != m_unary.end(); ++i)
    {
        UnaryRef op = *i;
        if (op->getOpcode() == opcode) {
            return op;
        }
    }
    return UnaryRef();
}

// find binary operator
BinaryRef Type::find(BinaryOperator::Opcode opcode, TypeRef operatorType)
{
    for (std::vector<BinaryRef>::iterator i = m_binary.begin(); i != m_binary.end(); ++i)
    {
        BinaryRef op = *i;
        if (op->getOpcode() == opcode && operatorType == op->getOperatorType()) {
            return op;
        }
    }
    return BinaryRef();
}

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