#include "kiwi/Script/StatementNode.hpp"
#include "location.hh"

using namespace kiwi;
using namespace kiwi::script;

StatementNode::StatementNode(const Location& location) : Node(location) {

}

ExpressionStatementNode::ExpressionStatementNode(ExpressionNode* node) : StatementNode(node->getLocation()), m_node(node) {

}

ExpressionStatementNode::~ExpressionStatementNode() {
    delete m_node;
}

ScopeStatementNode::ScopeStatementNode(const Location& location) : StatementNode(location), m_parentScope(0) {

}

ScopeStatementNode::ScopeStatementNode(ScopeStatementNode* parentScope, const Location& location) : StatementNode(location),  m_parentScope(parentScope) {

}

ScopeStatementNode::~ScopeStatementNode() {

}

// Variable node constructor
VariableNode::VariableNode(const String& name, ScopeStatementNode* parentScope, const Location& location)
: Node(location), m_name(name), m_parentScope(parentScope) {

}

// Left variable node constructor
LeftVariableNode::LeftVariableNode(VariableNode* node, const Location& location)
: LeftExpressionNode(location), m_node(node) {

}
// Right variable node constructor
RightVariableNode::RightVariableNode(VariableNode* node, const Location& location)
: ExpressionNode(location), m_node(node) {

}