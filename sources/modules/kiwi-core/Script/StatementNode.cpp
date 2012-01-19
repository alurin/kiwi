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
    VariableIterator vi, ve = m_variablesMap.end();
    for (vi = m_variablesMap.begin(); vi != ve; ++vi) {
        VariableNode* node = vi->second;
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

// Get variable from scope statement node
VariableNode* ScopeStatementNode::getVariable(const String& name) {
    VariableIterator result = m_variablesMap.find(name);
    kiwi_assert(result != m_variablesMap.end() && "Variable not found in scope");
    return result->second;
}

// Declare variable
VariableNode* ScopeStatementNode::declareVariable(const String& name, const Location& location) {
    VariableIterator result = m_variablesMap.find(name);
    kiwi_assert(result == m_variablesMap.end() && "Variable found in scope");
    VariableNode* node = new VariableNode(name, this, location);
    m_variablesMap.insert(std::make_pair(name, node));
    return node;
}