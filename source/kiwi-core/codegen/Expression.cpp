#include "kiwi/codegen/Expression.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

ExpressionGen::ExpressionGen(llvm::BasicBlock* block, llvm::Value* value)
: StatementGen(block), m_value(value)
{
}

ExpressionGen::ExpressionGen(const ExpressionGen& gen)
: StatementGen(gen), m_value(gen.m_value)
{
}

ExpressionGen::ExpressionGen(const StatementGen& gen, llvm::Value* value)
: StatementGen(gen), m_value(value)
{
}

ExpressionGen& ExpressionGen::operator=(const ExpressionGen& gen)
{
    StatementGen::operator=(gen);
    m_value = gen.m_value;
    return *this;
}