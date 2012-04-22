#include "kiwi/Codegen/Statement.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>

StatementGen::StatementGen(TypeRef owner, llvm::BasicBlock* block, llvm::Value* thisValue, llvm::Value* selfValue)
: m_owner(owner), m_context(&(block->getParent()->getContext())), m_module(block->getParent()->getParent()),
  m_function(block->getParent()), m_block(block), m_thisValue(thisValue), m_selfValue(selfValue)
{
}

StatementGen::StatementGen(const StatementGen& gen)
: m_owner(gen.m_owner), m_context(gen.m_context), m_module(gen.m_module), m_function(gen.m_function),
  m_block(gen.m_block), m_thisValue(gen.m_thisValue), m_selfValue(gen.m_selfValue)
{
}

StatementGen& StatementGen::operator=(const StatementGen& gen)
{
    m_owner     = gen.m_owner;
    m_context   = gen.m_context;
    m_module    = gen.m_module;
    m_function  = gen.m_function;
    m_block     = gen.m_block;
    m_thisValue = gen.m_thisValue;
    m_selfValue = gen.m_selfValue;

    return *this;
}

