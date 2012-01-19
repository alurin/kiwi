#include "kiwi/Script/ExpressionNode.hpp"

using namespace kiwi;
using namespace kiwi::script;

// Expression node constructor
ExpressionNode::ExpressionNode(const Location& location) : Node(location) {

}

// Unary expression node constructor
UnaryExpressionNode::UnaryExpressionNode(ExpressionNode* node, Opcode opcode, const Location& location)
: ExpressionNode(location), m_opcode(opcode), m_node(node) {

}

// Unary expression node destructor
UnaryExpressionNode::~UnaryExpressionNode() {
    delete m_node;
}

// Binary expression node constructor
BinaryExpressionNode::BinaryExpressionNode(ExpressionNode* leftNode, ExpressionNode* rightNode, Opcode opcode, const Location& location)
: ExpressionNode(location), m_opcode(opcode), m_leftNode(leftNode), m_rightNode(rightNode) {

}

// Binary expression node destructor
BinaryExpressionNode::~BinaryExpressionNode() {
    delete m_leftNode;
    delete m_rightNode;
}

// Constant node constructor
ConstantNode::ConstantNode(const Location& location) : ExpressionNode(location) {

}

// Integer constant node constructor
IntegerNode::IntegerNode(int64_t value, const Location& location) : ConstantNode(location), m_value(value) {

}

// String constant node constructor
StringNode::StringNode(const String& value, const Location& location) : ConstantNode(location), m_value(value) {

}

// Char constant node constructor
CharNode::CharNode(UChar value, const Location& location) : ConstantNode(location), m_value(value) {

}

// Boolean constant node constructor
BooleanNode::BooleanNode(bool value, const Location& location) : ConstantNode(location), m_value(value) {

}

// Nullable constant node constructor
NullableNode::NullableNode(const Location& location) : ConstantNode(location) {

}
