#include "Emitter.hpp"

#include <llvm/InstrTypes.h>

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
LlvmBinaryOperator::LlvmBinaryOperator(llvm::Instruction::BinaryOps opcode)
: m_opcode(opcode) { }

// emit instruction for binary operator
ExpressionGen LlvmBinaryOperator::emit(const StatementGen& gen, const ExpressionGen& left, const ExpressionGen& right)
{
    llvm::Value* result = llvm::BinaryOperator::Create(m_opcode, left->getValue(), reight->getValue(), gen->getBlock());
    return ExpressionGen(gen, value);
}