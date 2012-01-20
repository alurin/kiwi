#include "kiwi/Script/NodeVisitor.hpp"
#include "kiwi/Script/ExpressionNode.hpp"
#include "kiwi/Script/StatementNode.hpp"

using namespace kiwi;
using namespace kiwi::script;

// Implement visitor pattern for StatementNode
void StatementNode::accept(NodeVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for ExpressionNode
void ExpressionNode::accept(NodeVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for LeftExpressionNode
void LeftExpressionNode::accept(NodeVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for VariableNode
void VariableNode::accept(NodeVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for UnaryExpressionNode
void UnaryExpressionNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for BinaryExpressionNode
void BinaryExpressionNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for AssignmentExpressionNode
void AssignmentExpressionNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for IntegerNode
void IntegerNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for BooleanNode
void BooleanNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for StringNode
void StringNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for CharNode
void CharNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for NullableNode
void NullableNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for RightVariableNode
void RightVariableNode::accept(ExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for LeftVariableNode
void LeftVariableNode::accept(LeftExpressionVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for ExpressionStatementNode
void ExpressionStatementNode::accept(StatementVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for ScopeStatementNode
void ScopeStatementNode::accept(StatementVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for ConditionalStatementNode
void ConditionalStatementNode::accept(StatementVisitor& visitor) {
    visitor.visit(this);
}

// Implement visitor pattern for ConditionLoopNode
void ConditionLoopNode::accept(StatementVisitor& visitor) {
    visitor.visit(this);
}