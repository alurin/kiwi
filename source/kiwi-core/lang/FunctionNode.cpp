#include "FunctionNode.hpp"

using namespace kiwi;
using namespace kiwi::lang;

ArgumentNode::ArgumentNode(FunctionNode* owner, const Identifier& name, TypeNode* type)
: o_owner(owner), m_name(name), m_type(type) { }

ArgumentNode::~ArgumentNode() {}

ScopeNode::ScopeNode(ScopeNode* parent)
: o_owner(parent->o_owner), o_parent(parent) { }

ScopeNode::ScopeNode(FunctionNode* parent)
: o_owner(parent), o_parent(0) { }

FunctionNode::FunctionNode(const Identifier& name, TypeNode* type)
: m_name(name), m_type(type), m_root(new ScopeNode(this))
{

}

FunctionNode::~FunctionNode()
{
    delete m_root;
}

ArgumentNode* FunctionNode::add(const Identifier& name, TypeNode* type)
{
    ArgumentNode* arg = new ArgumentNode(this, name, type);
    /// @todo Save argument in map
    m_args.insert(std::make_pair(name, arg));
    return arg;
}

LeftNode* ScopeNode::getLeftLocal(const Identifier& name)
{
    /// @todo implement
    return 0;
}

LeftNode* ScopeNode::getLeftInstance(const Identifier& name)
{
    /// @todo implement
    return 0;
}

RightNode* ScopeNode::getRightLocal(const Identifier& name)
{
    /// @todo implement
    return 0;
}

RightNode* ScopeNode::getRightInstance(const Identifier& name)
{
    /// @todo implement
    return 0;
}


#include <iostream>

void FunctionNode::dump()
{
    std::cout << this->m_name << "\n";
}