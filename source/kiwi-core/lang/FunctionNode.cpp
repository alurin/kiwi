#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "TypeNode.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Module.hpp"
#include <llvm/ADT/ArrayRef.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include <llvm/Constant.h>
#include <vector>

using namespace kiwi;
using namespace kiwi::lang;

NamedNode::NamedNode(FunctionNode* owner, TypeNode* type)
: o_owner(owner), m_type(type) { }

NamedNode::~NamedNode() {
    delete m_type;
}

ArgumentNode::ArgumentNode(FunctionNode* owner, const Identifier& name, TypeNode* type)
: NamedNode(owner, type), m_name(name) { }

ArgumentNode::~ArgumentNode() { }

VariableNode::VariableNode(ScopeNode* owner, const Identifier& name, TypeNode* type)
: NamedNode(owner->getOwner(), type), o_owner(owner), m_name(name) { }

VariableNode::~VariableNode() { }

ScopeNode::ScopeNode(ScopeNode* parent)
: StatementNode(parent) { }

ScopeNode::ScopeNode(FunctionNode* parent)
: StatementNode(parent) { }

ScopeNode::~ScopeNode()
{
    for (std::vector<StatementNode*>::iterator i = m_stmts.begin(); i != m_stmts.end(); ++i)
    {
        StatementNode* stmt = *i;
        delete stmt;
    }

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
    delete m_type;
    for (std::map<Identifier, ArgumentNode*>::iterator i = m_args.begin(); i != m_args.end(); ++i)
    {
        ArgumentNode* arg = i->second;
        delete arg;
    }
}

ExpressionNode::ExpressionNode(ScopeNode* parent, RightNode* expr)
: StatementNode(parent), m_expr(expr) { }

ExpressionNode::~ExpressionNode()
{
    delete m_expr;
}

ArgumentNode* FunctionNode::declare(const Identifier& name, TypeNode* type)
{
    ArgumentNode* arg = new ArgumentNode(this, name, type);
    m_args.insert(std::make_pair(name, arg));
    return arg;
}

ArgumentNode* FunctionNode::get(const Identifier& name)
{
    std::map<Identifier, ArgumentNode*>::iterator it = m_args.find(name);
    if (it != m_args.end()) {
        return it->second;
    } else {
        /// @todo Implement exception or error
    }
}

VariableNode* ScopeNode::declare(const Identifier& name, TypeNode* type)
{
    VariableNode* var = new VariableNode(this, name, type);
    m_vars.insert(std::make_pair(name, var));
    return var;
}

NamedNode* ScopeNode::get(const Identifier& name)
{
    std::map<Identifier, VariableNode*>::iterator it = m_vars.find(name);
    if (it != m_vars.end()) {
        return it->second;
    } else if (o_parent) {
        /// @todo Replace for create proxy
        return o_parent->get(name);
    } else {
        return o_owner->get(name);
    }
}

void ScopeNode::append(StatementNode* scope)
{
    m_stmts.push_back(scope);
}

void ScopeNode::append(RightNode* expr)
{
    append(new ExpressionNode(this, expr));
}

LeftNode* ArgumentNode::getLeft()
{
    return new ArgumentLeftNode(this);
}

RightNode* ArgumentNode::getRight()
{
    return new ArgumentRightNode(this);
}

LeftNode* VariableNode::getLeft()
{
    return new VariableLeftNode(this);
}

RightNode* VariableNode::getRight()
{
    return new VariableRightNode(this);
}

void FunctionNode::generate(TypeRef ownerType)
{
    ModuleRef module = ownerType->getModule();

    // collect nodes
    TypeRef     frontendResultType = m_type->get();
    llvm::Type* backendResultType  = frontendResultType->getVarType();

    // collect arguments
    std::vector<llvm::Type*>    backendArgs;
    std::vector<ArgumentRef>    frontendArgs;
    for (std::map<Identifier, ArgumentNode*>::iterator i = m_args.begin(); i != m_args.end(); ++i)
    {
        ArgumentNode* arg = i->second;
        TypeRef       frontend_type = arg->getType()->get();
        ArgumentRef   frontend_arg  = Argument::create(i->first, frontend_type);
        llvm::Type*   backend_type  = frontend_type->getVarType();

        backendArgs.push_back(backend_type);
        frontendArgs.push_back(frontend_arg);
        m_positions.push_back(arg);
    }


    llvm::FunctionType* backendType = llvm::FunctionType::get(backendResultType, llvm::makeArrayRef(backendArgs), false);
    m_method = ownerType->add(m_name, frontendResultType, frontendArgs);
    m_func   = llvm::Function::Create(backendType, llvm::GlobalValue::ExternalLinkage , m_name, module->getModule());
    m_method->setFunction(m_func);

    // emit mutable variables for arguments
    size_t j = 0;
    for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j)
    {
        ArgumentNode* arg = m_positions[j];
        i->setName(arg->getName());
    }
}

void FunctionNode::emit(TypeRef ownerType)
{
    llvm::BasicBlock* entry  = llvm::BasicBlock::Create(m_func->getContext(), "entry", m_func);

    // emit mutable variables for arguments
    size_t j = 0;
    for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j)
    {
        ArgumentNode* arg = m_positions[j];
        //if (!i->getType()->isPointerTy()) {
            llvm::AllocaInst* value = new llvm::AllocaInst(i->getType(), arg->getName(), entry);
            llvm::StoreInst*  store = new llvm::StoreInst(i, value, entry);

            VariableGen vargen(arg->getType()->get(), value);
            arg->setGenerator(vargen);
        // } else {
        //     llvm::PointerType* pointer = llvm::cast<llvm::PointerType>(i->getType());
        //     llvm::AllocaInst*  value   = new llvm::AllocaInst(pointer->getElementType(), arg->getName(), entry);
        //     llvm::StoreInst*   store   = new llvm::StoreInst(i, value, entry);

        //     VariableGen vargen(arg->getType()->get(), value);
        //     arg->setGenerator(vargen);
        // }
    }

    // emit instructions
    StatementGen gen(ownerType, entry);
    gen = m_root->emit(gen);

    /// emit terminator for last block
    if (!gen.getBlock()->getTerminator()) {
        llvm::Type* resultType = llvm::cast<llvm::FunctionType>(m_func->getType())->getReturnType();
        if (resultType->isVoidTy()) {
            llvm::ReturnInst::Create(gen.getContext(), gen.getBlock());
        } else {
            llvm::Value* result = llvm::Constant::getNullValue(resultType);
            llvm::ReturnInst::Create(gen.getContext(), result, gen.getBlock());
        }
    }
}

StatementGen ScopeNode::emit(const StatementGen& gen)
{
    // emit mutable variables
    for (std::map<Identifier, VariableNode*>::iterator i = m_vars.begin(); i != m_vars.end(); ++i)
    {
        VariableNode* var = i->second;

        TypeRef type             = var->getType()->get();
        llvm::Type* var_type     = type->getVarType();
        llvm::Value* var_default = llvm::Constant::getNullValue(var_type);
        llvm::AllocaInst* value  = new llvm::AllocaInst(var_type, i->first, gen.getBlock());
        new llvm::StoreInst(var_default, value, gen.getBlock());

        VariableGen vargen(type, value);
        var->setGenerator(vargen);
    }

    // emit statements and expressions
    StatementGen result = gen;
    for (std::vector<StatementNode*>::iterator i = m_stmts.begin(); i != m_stmts.end(); ++i)
    {
        StatementNode* stmt = *i;
        result = stmt->emit(result);
    }
    return result;
}

StatementGen ExpressionNode::emit(const StatementGen& gen)
{
    return m_expr->emit(gen);
}