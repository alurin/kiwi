#include "FunctionNode.hpp"
#include "ExpressionNode.hpp"

using namespace kiwi;
using namespace kiwi::lang;

ArgumentNode::ArgumentNode(FunctionNode* owner, const Identifier& name, TypeNode* type)
: o_owner(owner), m_name(name), m_type(type) { }

ArgumentNode::~ArgumentNode() {}

VariableNode::VariableNode(ScopeNode* owner, const Identifier& name, TypeNode* type)
: o_owner(owner), m_name(name), m_type(type) { }

VariableNode::~VariableNode() {}

ScopeNode::ScopeNode(ScopeNode* parent)
: o_owner(parent->o_owner), o_parent(parent) { }

ScopeNode::ScopeNode(FunctionNode* parent)
: o_owner(parent), o_parent(0) { }

ScopeNode::~ScopeNode()
{
    for (std::map<Identifier, VariableNode*>::iterator i = m_vars.begin(); i != m_vars.end(); ++i)
    {
        VariableNode* arg = i->second;
        delete arg;
    }
}

FunctionNode::FunctionNode(const Identifier& name, TypeNode* type)
: m_name(name), m_type(type), m_root(new ScopeNode(this))
{

}

FunctionNode::~FunctionNode()
{
    delete m_root;
    for (std::map<Identifier, ArgumentNode*>::iterator i = m_args.begin(); i != m_args.end(); ++i)
    {
        ArgumentNode* arg = i->second;
        delete arg;
    }
}

ArgumentNode* FunctionNode::declare(const Identifier& name, TypeNode* type)
{
    ArgumentNode* arg = new ArgumentNode(this, name, type);
    m_args.insert(std::make_pair(name, arg));
    return arg;
}

void ScopeNode::declare(const Identifier& name, TypeNode* type)
{
    VariableNode* var = new VariableNode(this, name, type);
    m_vars.insert(std::make_pair(name, var));
}

VariableNode* ScopeNode::get(const Identifier& name)
{
    std::map<Identifier, VariableNode*>::iterator it = m_vars.find(name);
    if (it != m_vars.end()) {
        return it->second;
    } else {
        return 0;
    }
}

LeftNode* VariableNode::getLeft()
{
    return new VariableLeftNode(this);
}

RightNode* VariableNode::getRight()
{
    return new VariableRightNode(this);
}


///=== DEBUG ===
#include <iostream>

void FunctionNode::dump()
{
    std::cout << this->m_name << "\n";
    for (std::map<Identifier, ArgumentNode*>::iterator i = m_args.begin(); i != m_args.end(); ++i)
    {
        std::cout << "  $" << i->first << "\n";
    }
}