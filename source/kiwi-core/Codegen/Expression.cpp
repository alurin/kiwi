#include "kiwi/Codegen/Expression.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

ExpressionGen::ExpressionGen(const ExpressionGen& gen)
: StatementGen(gen),  m_type(gen.m_type), m_value(gen.m_value)
{
}

ExpressionGen::ExpressionGen(const StatementGen& gen, TypeRef type, llvm::Value* value)
: StatementGen(gen), m_type(type), m_value(value)
{
}

ExpressionGen& ExpressionGen::operator=(const ExpressionGen& gen)
{
    StatementGen::operator=(gen);
    m_type  = gen.m_type;
    m_value = gen.m_value;
    return *this;
}
