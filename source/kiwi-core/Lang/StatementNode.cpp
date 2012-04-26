/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/assert.hpp"
#include "Driver.hpp"
#include "StatementNode.hpp"
#include "FunctionNode.hpp"
#include "ExpressionNode.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "../Codegen/Builder.hpp"

using namespace kiwi;
using namespace kiwi::lang;
using namespace kiwi::codegen;

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

// emit instructions for return statement
BlockBuilder ReturnStatement::emit(Driver& driver, BlockBuilder block) const {
    if (m_return) {
        ValueBuilder result = m_return->emit(driver, block);
        block.createReturn(result);
    } else {
        block.createReturn();
    }
    return block;
}

// emit instructions for print statement
BlockBuilder PrintStatement::emit(Driver& driver, BlockBuilder block) const {
    // emit operand
    ValueBuilder result = m_return->emit(driver, block);

    // find emitter
    Type* type = result.getType();
    UnaryOperator* op = type->findUnary(UnaryOperator::Print);

    // emit instruction
    if (op) {
        std::vector<ValueBuilder> args;
        args.push_back(result);
        return block.createCall(op, args);
    }
    KIWI_ERROR_AND_EXIT("not found print operator", getLocation());
}

/// emit instructions for statement
BlockBuilder ConditionalNode::emit(Driver& driver, BlockBuilder block) const {
    KIWI_NOT_IMPLEMENTED();
    // llvm::BasicBlock* blockTrue  = llvm::BasicBlock::Create(gen.getContext(), "true",  gen.getFunction());
    // llvm::BasicBlock* blockFalse = llvm::BasicBlock::Create(gen.getContext(), "false", gen.getFunction());
    // llvm::BasicBlock* blockNext  = llvm::BasicBlock::Create(gen.getContext(), "next",  gen.getFunction());

    // BlockBuilder genTrue(gen.getOwner(), blockTrue);
    // BlockBuilder genFalse(gen.getOwner(), blockFalse);
    // BlockBuilder genNext(gen.getOwner(), blockNext);

    // ValueBuilder result = m_cond->emit(driver, gen);
    // llvm::Value* cond = result.getValue();
    // if (!cond->getType()->isIntegerTy(1)) {
    //     KIWI_ERROR_AND_EXIT("Condition must be boolean", m_cond->getLocation());
    // }

    // /// Emit branches
    // if (m_trueStmt)  genTrue  = m_trueStmt->emit(driver, genTrue);
    // if (m_falseStmt) genFalse = m_falseStmt->emit(driver, genFalse);

    // llvm::IRBuilder<>(result.getBlock()).CreateCondBr(cond, blockTrue, blockFalse);
    // llvm::IRBuilder<>(genFalse.getBlock()).CreateBr(blockNext);
    // llvm::IRBuilder<>(genTrue.getBlock()).CreateBr(blockNext);

    // return genNext;
}

// emit instructions for statement
BlockBuilder InitStatement::emit(Driver& driver, BlockBuilder block) const {
    ExpressionNode* init = m_var->getInitilizator();
    kiwi_assert(init, "Initilizate varaible node created, but initilizator not found");
    ValueBuilder  value   = init->emit(driver, block);
    ValueBuilder* builder = m_var->findBuilder(block.getFunction());
    if (!builder)
        KIWI_ERROR_AND_EXIT("Not found value builder for store value in varaible", getLocation());
    return value.createStore(*builder, value);
}
