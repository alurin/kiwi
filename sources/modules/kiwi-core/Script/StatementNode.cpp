/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include <map>

#include "kiwi/Script/StatementNode.hpp"
#include "kiwi/Config.hpp"
#include "location.hh"

using namespace kiwi;
using namespace kiwi::script;

StatementNode::StatementNode(const Location& location) : Node(location) {

}

ExpressionStatementNode::ExpressionStatementNode(ExpressionNode* node) : StatementNode(node->getLocation()), m_node(node) {

}

ExpressionStatementNode::~ExpressionStatementNode() {
    delete m_node;
}

ScopeStatementNode::ScopeStatementNode(const Location& location) : StatementNode(location), m_parentScope(0) {

}

ScopeStatementNode::ScopeStatementNode(ScopeStatementNode* parentScope, const Location& location) : StatementNode(location),  m_parentScope(parentScope) {

}

// ScopeStatementNode destructor
ScopeStatementNode::~ScopeStatementNode() {
    int i, size = m_statements.size();
    for (i = 0; i < size; ++i) {
        StatementNode* statement = m_statements[i];
        delete statement;
    }

    VariableIterator vi, ve = m_variables.end();
    for (vi = m_variables.begin(); vi != ve; ++vi) {
        VariableNode* node = vi->second;
        if (node->getParentScope() == this)
            delete node;
    }
}

// Variable node constructor
VariableNode::VariableNode(const String& name, ScopeStatementNode* parentScope, const Location& location)
: Node(location), m_name(name), m_parentScope(parentScope) {

}

// Left variable node constructor
LeftVariableNode::LeftVariableNode(VariableNode* node, const Location& location)
: LeftExpressionNode(location), m_node(node) {

}

// Right variable node constructor
RightVariableNode::RightVariableNode(VariableNode* node, const Location& location)
: ExpressionNode(location), m_node(node) {

}

// ConditionalStatementNode constructor
ConditionalStatementNode::ConditionalStatementNode(ExpressionNode* conditional, StatementNode* trueStatement,
                                                    StatementNode* falseStatement, const Location& location)
: StatementNode(location),  m_conditional(conditional), m_trueStatement(trueStatement), m_falseStatement(falseStatement) {

}

// ConditionalStatementNode constructor
ConditionalStatementNode::ConditionalStatementNode(ExpressionNode* conditional, StatementNode* trueStatement,
                                                    const Location& location)
: StatementNode(location),  m_conditional(conditional), m_trueStatement(trueStatement), m_falseStatement(0) {

}

// ConditionalStatementNode destructor
ConditionalStatementNode::~ConditionalStatementNode() {
    delete m_conditional;
    delete m_trueStatement;
    delete m_falseStatement;
}

// Loop statement constructor
LoopNode::LoopNode(LoopNode* parentLoop, const Location& location)
: StatementNode(location), m_statementNode(0), m_parentLoop(parentLoop) {

}

// Loop statement constructor
LoopNode::LoopNode(StatementNode* statementNode, LoopNode* parentLoop, const Location& location)
: StatementNode(location), m_statementNode(statementNode), m_parentLoop(parentLoop) {

}

LoopNode::~LoopNode() {
    delete m_statementNode;
}

// Conditional loop node constructor
ConditionLoopNode::ConditionLoopNode(CheckPosition position, LoopNode* parentLoop, const Location& location)
: LoopNode(parentLoop, location), m_conditional(0), m_position(position) {

}

// Conditional loop node constructor
ConditionLoopNode::ConditionLoopNode(ExpressionNode* conditional, CheckPosition position, LoopNode* parentLoop,
                                        const Location& location)
: LoopNode(parentLoop, location), m_conditional(conditional), m_position(position) {

}

// Conditional loop node destructor
ConditionLoopNode::~ConditionLoopNode() {
    delete m_conditional;
}

// Get variable from scope statement node
VariableNode* ScopeStatementNode::getVariable(const String& name) {
    VariableIterator result = m_variables.find(name);
    if (result == m_variables.end()) {
        kiwi_assert(m_parentScope != 0 && "Variable not found in nearest scopes");
        VariableNode* node = m_parentScope->getVariable(name);
        m_variables.insert(std::make_pair(name, node));
        return node;
    }
    return result->second;
}

// Declare variable
VariableNode* ScopeStatementNode::declareVariable(const String& name, const Location& location) {
    VariableIterator result = m_variables.find(name);
    kiwi_assert(result == m_variables.end() && "Variable found in scope");
    VariableNode* node = new VariableNode(name, this, location);
    m_variables.insert(std::make_pair(name, node));
    return node;
}

// Add statement
void ScopeStatementNode::addStatement(StatementNode* statement) {
    if (statement) {
        m_statements.push_back(statement);
    }
}