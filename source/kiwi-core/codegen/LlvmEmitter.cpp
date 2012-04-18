#include "LlvmEmitter.hpp"

#include <llvm/InstrTypes.h>

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
LlvmBinaryOperator::LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode, TypeRef type)
: m_opcode(opcode), m_type(type) { }

// emit instruction for binary operator
ExpressionGen LlvmBinaryOperator::emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right)
{
    llvm::Value* result = llvm::BinaryOperator::Create(m_opcode, left.getValue(), right.getValue(), "bop", gen.getBlock());
    return ExpressionGen(gen, m_type, result);
}