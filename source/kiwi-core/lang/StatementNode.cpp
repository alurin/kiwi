#include "StatementNode.hpp"
#include "FunctionNode.hpp"
#include "ExpressionNode.hpp"
#include "kiwi/codegen/Expression.hpp"
#include "kiwi/codegen/Variable.hpp"
#include <llvm/Instructions.h>

using namespace kiwi;
using namespace kiwi::lang;
using namespace kiwi::codegen;

StatementNode::StatementNode(ScopeNode* parent)
: o_owner(parent->o_owner), o_parent(parent) { }

StatementNode::StatementNode(FunctionNode* parent)
: o_owner(parent), o_parent(0) { }

/// constructor
ReturnStatement::ReturnStatement(ScopeNode* parent)
: StatementNode(parent), m_result(0) {}

/// constructor
ReturnStatement::ReturnStatement(ScopeNode* parent, RightNode* result)
: StatementNode(parent), m_result(result) {}

/// emit instructions for statement
StatementGen ReturnStatement::emit(const StatementGen& gen)
{
    if (m_result) {
        /// @todo check equals of return type
        ExpressionGen result = m_result->emit(gen);
        llvm::ReturnInst::Create(gen.getContext(), result.getValue(), result.getBlock());
        return result;
    } else {
        /// @todo check equals of return type
        llvm::ReturnInst::Create(gen.getContext(), gen.getBlock());
    }
    return gen;
}