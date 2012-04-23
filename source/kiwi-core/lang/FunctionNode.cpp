#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "TypeNode.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Codegen/Method.hpp"
#include <llvm/ADT/ArrayRef.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constant.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include <vector>

using namespace kiwi;
using namespace kiwi::lang;
using namespace kiwi::codegen;

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

ScopeNode::~ScopeNode() {
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

FunctionNode::FunctionNode(const Identifier& name, TypeNode* thisType, TypeNode* resultType)
: m_name(name), m_this(thisType), m_type(resultType), m_root(new ScopeNode(this)), m_func(0) {

}

FunctionNode::~FunctionNode() {
    delete m_root;
    delete m_type;
    for (std::map<Identifier, ArgumentNode*>::iterator i = m_args.begin(); i != m_args.end(); ++i) {
        ArgumentNode* arg = i->second;
        delete arg;
    }
}

FieldNode::FieldNode(const Identifier& name, TypeNode* type)
: m_name(name), m_type(type) {

}

FieldNode::~FieldNode() {
    delete m_type;
}

ExpressionStatementNode::ExpressionStatementNode(ScopeNode* parent, ExpressionNode* expr)
: StatementNode(parent), m_expr(expr) { }

ExpressionStatementNode::~ExpressionStatementNode() {
    delete m_expr;
}

ArgumentNode* FunctionNode::declare(const Identifier& name, TypeNode* type) {
    ArgumentNode* arg = new ArgumentNode(this, name, type);
    m_args.insert(std::make_pair(name, arg));
    return arg;
}

ArgumentNode* FunctionNode::get(const Identifier& name) {
    std::map<Identifier, ArgumentNode*>::iterator it = m_args.find(name);
    if (it != m_args.end()) {
        return it->second;
    } else {
        /// @todo Implement exception or error
    }
}

VariableNode* ScopeNode::declare(const Identifier& name, TypeNode* type) {
    VariableNode* var = new VariableNode(this, name, type);
    m_vars.insert(std::make_pair(name, var));
    return var;
}

NamedNode* ScopeNode::get(const Identifier& name) {
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

void ScopeNode::append(StatementNode* scope) {
    m_stmts.push_back(scope);
}

void ScopeNode::append(ExpressionNode* expr) {
    append(new ExpressionStatementNode(this, expr));
}

MutableNode* ArgumentNode::getLeft() {
    return new ArgumentMutableNode(this);
}

ExpressionNode* ArgumentNode::getRight() {
    return new ArgumentExpressionNode(this);
}

MutableNode* VariableNode::getLeft() {
    return new VariableMutableNode(this);
}

ExpressionNode* VariableNode::getRight() {
    return new VariableExpressionNode(this);
}

void FieldNode::generate(Type* ownerType) {
    Type* resultType = m_type->get();
    ownerType->add(m_name, resultType);
}

void FunctionNode::generate(Type* ownerType) {
    Module* module   = ownerType->getModule();
    Type* resultType = m_type->get();
    std::vector<Type*> frontendArgs;

    // collect arguments
    for (std::map<Identifier, ArgumentNode*>::iterator i = m_args.begin(); i != m_args.end(); ++i) {
        ArgumentNode* arg = i->second;
        Type*         frontend_type = arg->getType()->get();

        frontendArgs.push_back(frontend_type);
        m_positions.push_back(arg);
    }

    m_method = ownerType->add(m_name, resultType, frontendArgs);
    m_func   = MethodEmitter(m_method).emitDefinition();

    // emit mutable variables for arguments
    size_t j = 0;
    for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j) {
        if (j) {
            ArgumentNode* arg = m_positions[j-1];
            i->setName(arg->getName());
        } else {
            i->setName("this");
        }
    }
}

void FunctionNode::emit(Type* ownerType) {
    llvm::BasicBlock* entry = llvm::BasicBlock::Create(m_func->getContext(), "entry", m_func);

    // emit mutable variables for arguments
    size_t j = 0;
    for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j) {
        if (j) {
            ArgumentNode* arg = m_positions[j-1];
            llvm::AllocaInst* value = new llvm::AllocaInst(i->getType(), arg->getName(), entry);
            llvm::StoreInst*  store = new llvm::StoreInst(i, value, entry);

            VariableGen vargen(arg->getType()->get(), value);
            arg->setGenerator(vargen);
        } else {
            /// @todo remove
            // thisValue = new llvm::AllocaInst(ownerType->getVarType(), "this", entry);
            // llvm::StoreInst* store = new llvm::StoreInst(i, thisValue, entry);
            //thisValue->setGenerator(vargen);
        }
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

StatementGen ScopeNode::emit(const StatementGen& gen) {
    // emit mutable variables
    for (std::map<Identifier, VariableNode*>::iterator i = m_vars.begin(); i != m_vars.end(); ++i)
    {
        VariableNode* var = i->second;

        Type* type             = var->getType()->get();
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

StatementGen ExpressionStatementNode::emit(const StatementGen& gen) {
    return m_expr->emit(gen);
}
