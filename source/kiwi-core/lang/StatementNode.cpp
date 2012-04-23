#include "StatementNode.hpp"
#include "FunctionNode.hpp"
#include "ExpressionNode.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Codegen/Emitter.hpp"
#include "kiwi/Codegen/Expression.hpp"
#include "kiwi/Codegen/Variable.hpp"
#include <llvm/Instructions.h>

using namespace kiwi;
using namespace kiwi::lang;
using namespace kiwi::codegen;

StatementNode::StatementNode(ScopeNode* parent)
: o_owner(parent->o_owner), o_parent(parent) { }

StatementNode::StatementNode(FunctionNode* parent)
: o_owner(parent), o_parent(0) { }

// constructor
ReturnStatement::ReturnStatement(ScopeNode* parent)
: StatementNode(parent), m_return(0) {}

// constructor
ReturnStatement::ReturnStatement(ScopeNode* parent, ExpressionNode* result)
: StatementNode(parent), m_return(result) {}

// destructor
ReturnStatement::~ReturnStatement()
{
    delete m_return;
}
// constructor
PrintStatement::PrintStatement(ScopeNode* parent, ExpressionNode* result)
: StatementNode(parent), m_return(result) {}

// destructor
PrintStatement::~PrintStatement()
{
    delete m_return;
}
// emit instructions for return statement
StatementGen ReturnStatement::emit(const StatementGen& gen)
{
    if (m_return) {
        /// @todo check equals of return type
        ExpressionGen result = m_return->emit(gen);
        llvm::ReturnInst::Create(gen.getContext(), result.getValue(), result.getBlock());
        return result;
    } else {
        /// @todo check equals of return type
        llvm::ReturnInst::Create(gen.getContext(), gen.getBlock());
    }
    return gen;
}

// emit instructions for print statement
StatementGen PrintStatement::emit(const StatementGen& gen)
{
    // emit operand
    ExpressionGen result = m_return->emit(gen);

    // find emitter
    Type* type = result.getType();
    UnaryOperator* op = type->find(UnaryOperator::PRINT);

    // emit instruction
    if (op) {
        return op->getEmitter()->emit(result, result);
    }
    throw "not found unary operator";
}
