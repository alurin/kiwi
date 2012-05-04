/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Driver.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "TypeNode.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Type.hpp"
#include "../Codegen/Builder.hpp"
#include <vector>

using namespace kiwi;
using namespace kiwi::lang;

NamedNode::NamedNode(FunctionNode* owner, TypeNode* type)
: o_owner(owner), m_type(type) { }

NamedNode::~NamedNode() {
    delete m_type;
    for (BuilderMap::const_iterator i = m_builders.begin(); i != m_builders.end(); ++i) {
        ValueBuilder* builder = i->second;
        delete builder;
    }
}

ArgumentNode::ArgumentNode(FunctionNode* owner, const Identifier& name, TypeNode* type)
: NamedNode(owner, type), m_name(name) { }

ArgumentNode::~ArgumentNode() { }

VariableNode::VariableNode(ScopeNode* owner, const Identifier& name, TypeNode* type, ExpressionNode* expr)
: NamedNode(owner->getOwner(), type), o_owner(owner), m_name(name), m_init(expr) {
}

VariableNode::~VariableNode() {
    delete m_init;
}

ScopeNode::ScopeNode(ScopeNode* parent)
: StatementNode(parent) { }

ScopeNode::ScopeNode(FunctionNode* parent)
: StatementNode(parent) { }

ScopeNode::~ScopeNode() {
    for (std::vector<StatementNode*>::iterator i = m_stmts.begin(); i != m_stmts.end(); ++i) {
        StatementNode* stmt = *i;
        delete stmt;
    }

    for (std::map<Identifier, VariableNode*>::iterator i = m_vars.begin(); i != m_vars.end(); ++i) {
        VariableNode* arg = i->second;
        delete arg;
    }
}

FunctionNode::FunctionNode(const Identifier& name, TypeNode* thisType, TypeNode* returnType)
: m_name(name), m_this(thisType), m_type(returnType), m_root(new ScopeNode(this)), m_func(0) {

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

/// insert allocation
void NamedNode::insertBuilder(llvm::Function* func, ValueBuilder* builder) {
    m_builders.insert(std::make_pair(func, builder));
}

/// find builder
ValueBuilder* NamedNode::findBuilder(llvm::Function* func) {
    BuilderMap::const_iterator i = m_builders.find(func);
    if (i != m_builders.end()) {
        return i->second;
    }
    return 0;
}

ArgumentNode* FunctionNode::declare(const Identifier& name, TypeNode* type, const location& loc) {
    ArgumentNode* arg = new ArgumentNode(this, name, type);
    m_positions.push_back(arg);
    m_args.insert(std::make_pair(name, arg));
    arg->setLocation(loc);
    return arg;
}

ArgumentNode* FunctionNode::get(const Identifier& name) {
    std::map<Identifier, ArgumentNode*>::iterator it = m_args.find(name);
    if (it != m_args.end()) {
        return it->second;
    } else {
        throw LangException()
                << exception_format("Variable '%1%' not found in current scope", name);
    }
}
  // declare scope variable with initilizator
VariableNode* ScopeNode::declare(const Identifier& name, TypeNode* type, const location& loc) {
    VariableNode* var = new VariableNode(this, name, type, 0);
    m_vars.insert(std::make_pair(name, var));
    var->setLocation(loc);
    return var;
}

// declare scope variable with initilizator
VariableNode* ScopeNode::declare(const Identifier& name, TypeNode* type, ExpressionNode* expr, const location& loc) {
    VariableNode* var = new VariableNode(this, name, type, expr);
    m_vars.insert(std::make_pair(name, var));
    var->setLocation(loc);
    return var;
}

// declare scope variable with initilizator and auto type
VariableNode* ScopeNode::declare(const Identifier& name, ExpressionNode* expr, const location& loc) {
    VariableNode* var = new VariableNode(this, name, 0, expr);
    m_vars.insert(std::make_pair(name, var));
    var->setLocation(loc);
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
    if (scope) {
        m_stmts.push_back(scope);
    }
}

void ScopeNode::append(ExpressionNode* expr) {
    if (expr) {
        append(new ExpressionStatementNode(this, expr));
    }
}

MutableNode* NamedNode::getLeft() {
    return new NamedMutableNode(this);
}

ExpressionNode* NamedNode::getRight() {
    return new NamedExpressionNode(this);
}

void FieldNode::generateMember(Driver& driver, TypePtr ownerType) {
    TypePtr returnType = m_type->get(driver);
    ownerType->addField(m_name, returnType);
}

void FunctionNode::generateMember(Driver& driver, TypePtr ownerType) {
    ModulePtr module   = ownerType->getModule();
    TypePtr returnType = m_type->get(driver);
    std::vector<TypePtr> frontendArgs;

    // collect arguments
    for (std::vector<ArgumentNode*>::iterator i = m_positions.begin(); i != m_positions.end(); ++i) {
        ArgumentNode* arg           = *i;
        TypePtr         frontend_type = arg->getType()->get(driver);
        frontendArgs.push_back(frontend_type);
    }
    m_method = ownerType->addMethod(m_name, returnType, frontendArgs);
}

#include <llvm/Instructions.h>
#include <llvm/Function.h>

void FunctionNode::generateIRSignature(Driver& driver, TypePtr owner) {
    m_func = FunctionBuilder(m_method).getFunction();
    Identifier fullName = m_method->getOwnerType()->getName() + "::" + m_method->getName();
    m_func->setName(fullName);
}

void FunctionNode::generateIRCode(Driver& driver, TypePtr ownerType) {
    FunctionBuilder func(m_method);
    BlockBuilder entry = func.createBlock("entry");
    // emit mutable variables for arguments
    size_t j = 0;
    for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j) {
        if (j) {
            kiwi_assert(j-1 < m_positions.size(), "Ops... This is not worked");
            ArgumentNode* arg = m_positions[j-1];

            // add mutable for arguments
            TypePtr type = arg->getType()->get(driver);
            ValueBuilder variable = entry.createVariable(arg->getName(), type, false);
            /// @todo move store to builder
            llvm::StoreInst*  store = new llvm::StoreInst(i, variable.getValue(), entry.getBlock());

            // save information
            arg->insertBuilder(m_func, new ValueBuilder(variable));
        } else {
            /// this or self is special arguments: not mutable
            i->setName("this");
        }
    }

    // // emit instructions
    entry = m_root->emit(driver, entry);
    entry.createTrailReturn();
}

BlockBuilder ScopeNode::emitImpl(Driver& driver, BlockBuilder block) const {
    // emit mutable variables
    for (std::map<Identifier, VariableNode*>::const_iterator i = m_vars.begin(); i != m_vars.end(); ++i) {
        VariableNode* var = i->second;
        if (!var->getInitilizator()) {
            TypePtr type = var->getType()->get(driver);
            ValueBuilder vargen = block.createVariable(var->getName(), type); // not spaun new blocks
            ValueBuilder* builder = new ValueBuilder(vargen);
            var->insertBuilder(block.getFunction(), builder);
        }
    }

    // emit statements and expressions
    for (std::vector<StatementNode*>::const_iterator i = m_stmts.begin(); i != m_stmts.end(); ++i) {
        StatementNode* stmt = *i;
        block = stmt->emit(driver, block);
    }
    return block;
}

BlockBuilder ExpressionStatementNode::emitImpl(Driver& driver, BlockBuilder block) const {
    return m_expr->emit(driver, block);
}
