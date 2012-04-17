#include "kiwi/codegen/Variable.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

VariableGen::VariableGen() { }

VariableGen::VariableGen(llvm::Value* value)
: m_value(value) { }

VariableGen::VariableGen(const VariableGen& gen)
: m_value(gen.m_value) { }

VariableGen& VariableGen::operator=(const VariableGen& gen)
{
    m_value = gen.m_value;
    return *this;
}