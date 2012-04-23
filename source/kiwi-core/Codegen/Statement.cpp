#include "kiwi/Codegen/Statement.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <assert.h>

StatementGen::StatementGen(Type* owner, llvm::BasicBlock* block)
: m_owner(owner), m_context(&(block->getParent()->getContext())), m_module(block->getParent()->getParent()),
  m_function(block->getParent()), m_block(block) {
}

StatementGen::StatementGen(const StatementGen& gen)
: m_owner(gen.m_owner), m_context(gen.m_context), m_module(gen.m_module), m_function(gen.m_function),
  m_block(gen.m_block) {
}

StatementGen& StatementGen::operator=(const StatementGen& gen) {
    m_owner     = gen.m_owner;
    m_context   = gen.m_context;
    m_module    = gen.m_module;
    m_function  = gen.m_function;
    m_block     = gen.m_block;
    return *this;
}
