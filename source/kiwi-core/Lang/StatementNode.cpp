#include "Driver.hpp"
#include "StatementNode.hpp"
#include "FunctionNode.hpp"
#include "ExpressionNode.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Codegen/Emitter.hpp"
#include "kiwi/Codegen/Expression.hpp"
#include "kiwi/Codegen/Variable.hpp"
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>
#include <llvm/Support/IRBuilder.h>

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

/// constructor
ConditionalNode::ConditionalNode(ScopeNode* parent, ExpressionNode* cond, StatementNode* trueStmt, StatementNode* falseStmt)
: StatementNode(parent), m_cond(cond) , m_trueStmt(trueStmt) , m_falseStmt(falseStmt) {
}

/// destructor
ConditionalNode::~ConditionalNode() {

}

// emit instructions for return statement
StatementGen ReturnStatement::emit(Driver& driver, const StatementGen& gen) {
    if (m_return) {
        /// @todo check equals of return type
        ExpressionGen result = m_return->emit(driver, gen);
        llvm::ReturnInst::Create(gen.getContext(), result.getValue(), result.getBlock());
        return result;
    } else {
        /// @todo check equals of return type
        llvm::ReturnInst::Create(gen.getContext(), gen.getBlock());
    }
    return gen;
}

// emit instructions for print statement
StatementGen PrintStatement::emit(Driver& driver, const StatementGen& gen) {
    // emit operand
    ExpressionGen result = m_return->emit(driver, gen);

    // find emitter
    Type* type = result.getType();
    UnaryOperator* op = type->find(UnaryOperator::Print);

    // emit instruction
    if (op) {
        return op->getEmitter()->emit(result, result);
    }
    KIWI_ERROR_AND_EXIT("not found unary operator", getLocation());
}

/// emit instructions for statement
StatementGen ConditionalNode::emit(Driver& driver, const StatementGen& gen) {
    llvm::BasicBlock* blockTrue  = llvm::BasicBlock::Create(gen.getContext(), "true",  gen.getFunction());
    llvm::BasicBlock* blockFalse = llvm::BasicBlock::Create(gen.getContext(), "false", gen.getFunction());
    llvm::BasicBlock* blockNext  = llvm::BasicBlock::Create(gen.getContext(), "next",  gen.getFunction());

    StatementGen genTrue(gen.getOwner(), blockTrue);
    StatementGen genFalse(gen.getOwner(), blockFalse);
    StatementGen genNext(gen.getOwner(), blockNext);

    ExpressionGen result = m_cond->emit(driver, gen);
    llvm::Value* cond = result.getValue();
    if (!cond->getType()->isIntegerTy(1)) {
        KIWI_ERROR_AND_EXIT("Condition must be boolean", m_cond->getLocation());
    }

    /// Emit branches
    if (m_trueStmt)  genTrue  = m_trueStmt->emit(driver, genTrue);
    if (m_falseStmt) genFalse = m_falseStmt->emit(driver, genFalse);

    llvm::IRBuilder<>(result.getBlock()).CreateCondBr(cond, blockTrue, blockFalse);
    llvm::IRBuilder<>(genFalse.getBlock()).CreateBr(blockNext);
    llvm::IRBuilder<>(genTrue.getBlock()).CreateBr(blockNext);

    return genNext;
}
