#include "LlvmEmitter.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <llvm/InstrTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
LlvmZeroUnaryOperator::LlvmZeroUnaryOperator(llvm::Instruction::BinaryOps opcode, TypeRef type)
: m_opcode(opcode), m_type(type) { }

// constructor
LlvmBinaryOperator::LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode, TypeRef type)
: m_opcode(opcode), m_type(type) { }

// constructor
LlvmICompareOperator::LlvmICompareOperator(llvm::CmpInst::Predicate predicate, ContextRef context)
: m_predicate(predicate), m_context(context) { }

// emit instruction for interger unary operator
ExpressionGen LlvmZeroUnaryOperator::emit(const StatementGen& gen, const ExpressionGen& value)
{
    llvm::APInt cst(32, 0, false);
    llvm::ConstantInt* zero = llvm::ConstantInt::get(gen.getContext(), cst);

    llvm::Value* result = llvm::BinaryOperator::Create(m_opcode, zero, value.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, m_type, result);
}

// emit instruction for binary operator
ExpressionGen LlvmBinaryOperator::emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right)
{
    llvm::Value* result = llvm::BinaryOperator::Create(m_opcode, left.getValue(), right.getValue(), "", gen.getBlock());
    return ExpressionGen(gen, m_type, result);
}

// emit instruction for binary operator
ExpressionGen LlvmICompareOperator::emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right)
{
    // llvm::Value* result = llvm::BinaryOperator::Create(m_predicate, left.getValue(), right.getValue(), "", gen.getBlock());
    llvm::Value* result = new llvm::ICmpInst(*(gen.getBlock()), m_predicate, left.getValue(), right.getValue(), "");
    return ExpressionGen(gen, BoolType::get(m_context), result);
}