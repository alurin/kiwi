#include "kiwi/Codegen/Variable.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

VariableGen::VariableGen() { }

VariableGen::VariableGen(TypeRef type, llvm::Value* value)
: m_type(type), m_value(value) { }

VariableGen::VariableGen(const VariableGen& gen)
: m_type(gen.m_type), m_value(gen.m_value) { }

VariableGen& VariableGen::operator=(const VariableGen& gen)
{
    m_type  = gen.m_type;
    m_value = gen.m_value;
    return *this;
}
