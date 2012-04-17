#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "TypeNode.hpp"

#include "kiwi/Module.hpp"

#include <llvm/ADT/ArrayRef.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>

#include <vector>

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
: m_name(name), m_type(type), m_root(new ScopeNode(this)), m_func(0)
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

void FunctionNode::generate(ModuleRef module)
{
    llvm::Type* resultType = m_type->generate(module);
    std::vector<llvm::Type*> argTypes;
    std::vector<Identifier>  argNames;

    for (std::map<Identifier, ArgumentNode*>::iterator i = m_args.begin(); i != m_args.end(); ++i)
    {
        ArgumentNode* arg = i->second;
        llvm::Type* arg_type = arg->getType()->generate(module);

        argTypes.push_back(arg_type);
        argNames.push_back(arg->getName());
    }

    llvm::FunctionType* type = llvm::FunctionType::get(resultType, llvm::makeArrayRef(argTypes), false);
    m_func                   = llvm::Function::Create(type, llvm::GlobalValue::ExternalLinkage , "", module->getModule());

    size_t j = 0;
    for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j)
    {
        i->setName(argNames[j]);
    }

    m_root->generate(module);
}

void ScopeNode::generate(ModuleRef module)
{
    llvm::Function* func = o_owner->getFunction();
    llvm::BasicBlock* block = llvm::BasicBlock::Create(func->getContext(), "entry", func);
}