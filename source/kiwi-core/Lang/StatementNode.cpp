/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Driver.hpp"
#include "StatementNode.hpp"
#include "FunctionNode.hpp"
#include "ExpressionNode.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "../Codegen/Builder.hpp"

using namespace kiwi;
using namespace kiwi::lang;

StatementNode::StatementNode(ScopeNode* parent)
: o_owner(parent->o_owner), o_parent(parent) {
}

StatementNode::StatementNode(FunctionNode* parent)
: o_owner(parent), o_parent(0) {
}

// constructor
ReturnStatement::ReturnStatement(ScopeNode* parent)
: StatementNode(parent), m_return(0) {

}

// constructor
ReturnStatement::ReturnStatement(ScopeNode* parent, ExpressionNode* result)
: StatementNode(parent), m_return(result) {

}

// destructor
ReturnStatement::~ReturnStatement() {
    delete m_return;
}
// constructor
PrintStatement::PrintStatement(ScopeNode* parent, ExpressionNode* result)
: StatementNode(parent), m_return(result) {

}

// destructor
PrintStatement::~PrintStatement() {
    delete m_return;
}

// constructor
ConditionalNode::ConditionalNode(ScopeNode* parent, ExpressionNode* cond, StatementNode* trueStmt, StatementNode* falseStmt)
: StatementNode(parent), m_cond(cond) , m_trueStmt(trueStmt) , m_falseStmt(falseStmt) {
}

// destructor
ConditionalNode::~ConditionalNode() {

}
// constructor
InitStatement::InitStatement(ScopeNode* parent, VariableNode* var)
: StatementNode(parent), m_var(var) {
}

/// emit instructions for statement
BlockBuilder StatementNode::emit(Driver& driver, BlockBuilder block) const {
    KIWI_EXCEPTION_ADD_LOCATION({
        return emitImpl(driver, block);
    }, getLocation());
}

// emit instructions for return statement
BlockBuilder ReturnStatement::emitImpl(Driver& driver, BlockBuilder block) const {
    if (m_return) {
        ValueBuilder result = m_return->emit(driver, block);
        block.createReturn(result);
    } else {
        block.createReturn();
    }
    return block;
}

// emit instructions for print statement
BlockBuilder PrintStatement::emitImpl(Driver& driver, BlockBuilder block) const {
    // emit operand
    ValueBuilder result = m_return->emit(driver, block);

    // find emitter
    TypePtr type = result.getType();
    MethodPtr op = type->findUnary(Member::Print);

    // emit instruction
    if (op) {
        std::vector<ValueBuilder> args;
        args.push_back(result);
        return block.createCall(op, args);
    }

    throw LangException()
            << exception_format("Not found rules for print value of '%1%' ", result.getType()->getName())
            << exception_location(to_location(this));
}

/// emit instructions for statement
BlockBuilder ConditionalNode::emitImpl(Driver& driver, BlockBuilder block) const {
    BlockBuilder blockTrue  = block.createBlock("true");
    BlockBuilder blockFalse = block.createBlock("false");
    BlockBuilder blockNext  = block.createBlock("next");
    ValueBuilder result     = m_cond->emit(driver, block);

    /// Emit branches
    if (m_trueStmt)  blockTrue  = m_trueStmt->emit(driver, blockTrue);
    if (m_falseStmt) blockFalse = m_falseStmt->emit(driver, blockFalse);

    result.createCond(result, blockTrue, blockFalse);
    blockFalse.createBr(blockNext);
    blockTrue.createBr(blockNext);

    return blockNext;
}

// emit instructions for statement
BlockBuilder InitStatement::emitImpl(Driver& driver, BlockBuilder block) const {
    ExpressionNode* init = m_var->getInitilizator();
    kiwi_assert(init, "Initilizate varaible node created, but initilizator not found");

    // init value for variable
    ValueBuilder value = init->emit(driver, block);

    // get variable type
    TypePtr type;
    if (m_var->getType() != 0) {
        type = m_var->getType()->get(driver);
    } else {
        type = value.getType();
    }

    // allocate variable and store init value
    ValueBuilder vargen   = block.createVariable(m_var->getName(), type, false);
    ValueBuilder* builder = new ValueBuilder(vargen);
    m_var->insertBuilder(block.getFunction(), builder);
    return vargen.createStore(*builder, value);
}
