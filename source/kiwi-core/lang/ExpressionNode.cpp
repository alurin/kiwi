#include "ExpressionNode.hpp"

using namespace kiwi;
using namespace kiwi::lang;

BinaryNode::BinaryNode(OpCode opcode, RightNode* left, RightNode* right, bool logic)
: m_opcode(opcode), m_left(left), m_right(right), m_logic(logic)
{}

BinaryNode::~BinaryNode()
{
    delete m_left;
    delete m_right;
}

UnaryNode::UnaryNode(OpCode opcode, RightNode* value, bool post)
: m_opcode(opcode), m_value(value), m_post(post)
{}

UnaryNode::~UnaryNode()
{
    delete m_value;
}

AssignNode::AssignNode(LeftNode* left, RightNode* right)
: m_left(left), m_right(right)
{

}

AssignNode::~AssignNode()
{
    delete m_left;
    delete m_right;
}

VariableLeftNode::VariableLeftNode(VariableNode* var)
: o_var(var) { }

VariableRightNode::VariableRightNode(VariableNode* var)
: o_var(var) { }

ArgumentLeftNode::ArgumentLeftNode(ArgumentNode* arg)
: o_arg(arg) { }

ArgumentRightNode::ArgumentRightNode(ArgumentNode* arg)
: o_arg(arg) { }

IntegerConstNode::IntegerConstNode(int32_t value)
: m_value(value) { }