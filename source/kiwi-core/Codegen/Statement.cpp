#include "kiwi/Codegen/Statement.hpp"
#include <llvm/Function.h>

using namespace kiwi;
using namespace kiwi::codegen;


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
