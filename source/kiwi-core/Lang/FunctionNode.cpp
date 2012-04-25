#include "kiwi/assert.hpp"
#include "Driver.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "TypeNode.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Type.hpp"
#include "../Codegen/Builder.hpp"
#include "../Codegen/Method.hpp"
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

VariableNode::VariableNode(ScopeNode* owner, const Identifier& name, TypeNode* type, ExpressionNode* expr)
: NamedNode(owner->getOwner(), type), o_owner(owner), m_name(name), m_init(expr) {
}

VariableNode::~VariableNode() {
    // delete m_init; initilisator owned by expression statement, not varaible
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
    m_positions.push_back(arg);
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
  // declare scope variable with initilizator
VariableNode* ScopeNode::declare(const Identifier& name, TypeNode* type) {
    VariableNode* var = new VariableNode(this, name, type, 0);
    m_vars.insert(std::make_pair(name, var));
    return var;
}

// declare scope variable with initilizator
VariableNode* ScopeNode::declare(const Identifier& name, TypeNode* type, ExpressionNode* expr) {
    VariableNode* var = new VariableNode(this, name, type, expr);
    m_vars.insert(std::make_pair(name, var));
    return var;
}

// declare scope variable with initilizator and auto type
VariableNode* ScopeNode::declare(const Identifier& name, ExpressionNode* expr) {
    VariableNode* var = new VariableNode(this, name, 0, expr);
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
    if (scope) {
        m_stmts.push_back(scope);
    }
}

void ScopeNode::append(ExpressionNode* expr) {
    if (expr) {
        append(new ExpressionStatementNode(this, expr));
    }
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

void FieldNode::generateMember(Driver& driver, Type* ownerType) {
    Type* resultType = m_type->get(driver);
    ownerType->addField(m_name, resultType);
}

void FunctionNode::generateMember(Driver& driver, Type* ownerType) {
    Module* module   = ownerType->getModule();
    Type* resultType = m_type->get(driver);
    std::vector<Type*> frontendArgs;

    // collect arguments
    for (std::vector<ArgumentNode*>::iterator i = m_positions.begin(); i != m_positions.end(); ++i) {
        ArgumentNode* arg           = *i;
        Type*         frontend_type = arg->getType()->get(driver);
        frontendArgs.push_back(frontend_type);
    }
    m_method = ownerType->addMethod(m_name, resultType, frontendArgs);
}

void FunctionNode::generateIRSignature(Driver& driver, Type* owner) {
    m_func = MethodEmitter(m_method).emitDefinition();
}

void FunctionNode::generateIRCode(Driver& driver, Type* ownerType) {
    //KIWI_NOT_IMPLEMENTED();
    FunctionBuilder func(m_func, m_method);
    BlockBuilder entry = func.createBlock("entry");
    // // emit mutable variables for arguments
    // size_t j = 0;
    // for (llvm::Function::arg_iterator i = m_func->arg_begin(); i != m_func->arg_end(); ++i, ++j) {
    //     if (j) {
    //         kiwi_assert(j-1 < m_positions.size(), "Ops... This is not worked");
    //         ArgumentNode* arg = m_positions[j-1];

    //         // set argument name
    //         i->setName(arg->getName());

    //         // add mutable for arguments
    //         llvm::AllocaInst* value = new llvm::AllocaInst(i->getType(), arg->getName(), entry);
    //         llvm::StoreInst*  store = new llvm::StoreInst(i, value, entry);

    //         // save information
    //         VariableGen vargen(arg->getType()->get(driver), value);
    //         arg->setGenerator(vargen);
    //     } else {
    //         i->setName("this");
    //     }
    // }

    // // emit instructions
    entry = m_root->emit(driver, entry);
    entry.createTrailReturn();
}

BlockBuilder ScopeNode::emit(Driver& driver, BlockBuilder block) const {
    // emit mutable variables
    for (std::map<Identifier, VariableNode*>::const_iterator i = m_vars.begin(); i != m_vars.end(); ++i) {
        VariableNode* var = i->second;
        Type* type = 0;

        // get type
        if (var->getType() != 0) {
            type = var->getType()->get(driver);
        }

        // allocate and init variable
        if (ExpressionNode* init = var->getInitilizator()) {
            ValueBuilder expr = init->emit(driver, block);
            ValueBuilder vargen = block.createVariable(var->getName(), type ?: expr.getType(), false);
            KIWI_DUMP("Store information about variable not implemented");
        } else {
            ValueBuilder vargen = block.createVariable(var->getName(), type); // not spaun new blocks
            KIWI_DUMP("Store information about variable not implemented");
        }

    //     Type* type               = 0;
    //     llvm::Value* var_default = 0;

    //     if (var->getInitilizator()) {
    //         ExpressionNode* init = var->getInitilizator();
    //         ValueBuilder value  = init->emit(driver, block);
    //         block = value;

    //         // store information about auto type
    //         type        = value.getType();
    //         var_default = value.getValue();
    //         var->setType(new ConcreteTypeNode(type));
    //     } else {
    //         type        = var->getType()->get(driver);
    //         var_default = llvm::Constant::getNullValue(type->getVarType());
    //     }
    //     llvm::Type* var_type = type->getVarType();

    //     // initilizate variable
    //     llvm::AllocaInst* value  = new llvm::AllocaInst(var_type, i->first, block.getBlock());
    //     new llvm::StoreInst(var_default, value, block.getBlock());

    //     VariableGen vargen(type, value);
    //     var->setGenerator(vargen);
    }

    // emit statements and expressions
    for (std::vector<StatementNode*>::const_iterator i = m_stmts.begin(); i != m_stmts.end(); ++i) {
        StatementNode* stmt = *i;
        block = stmt->emit(driver, block);
    }
    return block;
}

BlockBuilder ExpressionStatementNode::emit(Driver& driver, BlockBuilder block) const {
    KIWI_NOT_IMPLEMENTED();
    //return m_expr->emit(driver, block);
}
