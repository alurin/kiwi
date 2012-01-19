/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "Driver.hpp"
#include "Lexer.hpp"
#include "kiwi/Engine.hpp"
#include "kiwi/Script/Driver.hpp"
#include "kiwi/Script/StatementNode.hpp"
#include "kiwi/Config.hpp"

#include <fstream>
#include <sstream>

using namespace kiwi;
using namespace kiwi::script;

bool Driver::s_debug = false;

DriverImpl::DriverImpl(Engine* engine) : m_engine(engine), m_lexer(0) {

}

DriverImpl::~DriverImpl() {
    // remove this after change parent AST for scope statement node
    while(!m_scopeStack.empty()) {
        ScopeStatementNode* scope = m_scopeStack.top();
        m_scopeStack.pop();
        delete scope;
    }
}

Path DriverImpl::getStreamNameUTF8() const {
    if (m_streamNameUTF8.size() == 0) {
        m_streamNameUTF8 = m_streamName.toUTF8String(m_streamNameUTF8);
    }
    return m_streamNameUTF8;
}

/// @todo exception if error in parser or lexer
RootNode* DriverImpl::parseStream(std::istream& in, const String& sname) {
    m_streamName = sname;

    // create root script node
    Location location(sname);
    ScopeStatementNode* rootScope = new ScopeStatementNode(location);
    m_scopeStack.push(rootScope);

    // create lexer
    Lexer scanner(*this, &in);
    scanner.set_debug(Driver::isDebugMode());
    this->m_lexer = &scanner;

    // create parse
    Parser parser(*this, scanner);
    parser.set_debug_level(Driver::isDebugMode());

    // parse
    (parser.parse() == 0);
    return 0;
}

RootNode* Driver::parseStream(Engine* engine, std::istream& in, const String& sname) {
    DriverImpl impl(engine);
    return impl.parseStream(in, sname);
}

/// @todo exception if file not found
RootNode* Driver::parseFile(Engine* engine, const Path& filename) {
    const char* sname = filename.c_str();
    std::ifstream in(sname);
    if (!in.good()) return 0;
    return parseStream(engine, in, sname);
}

RootNode* Driver::parseString(Engine* engine, const std::string &input, const String& sname) {
    std::istringstream iss(input);
    return parseStream(engine, iss, sname);
}

// Push scope statement node in stack
void DriverImpl::pushScope( ScopeStatementNode* scopeStatement ) {
    m_scopeStack.push(scopeStatement);
}

// Pop scope statement node from stack
ScopeStatementNode* DriverImpl::popScope() {
    kiwi_assert(!m_scopeStack.empty() && "Scope stack is empty");
    ScopeStatementNode* scope = m_scopeStack.top();
    m_scopeStack.pop();
    return scope;
}

// Peak scope statement node from stack
ScopeStatementNode* DriverImpl::peakScope() {
    kiwi_assert(!m_scopeStack.empty() && "Scope stack is empty");
    return m_scopeStack.top();
}

// Get variable from current scope
VariableNode* DriverImpl::getVariable(const String& name) {
    ScopeStatementNode* scope = peakScope();
    return scope->getVariable(name);
}

// Declare variable in current scope
VariableNode* DriverImpl::declareVariable(const String& name, const Location& location) {
    ScopeStatementNode* scope = peakScope();
    return scope->declareVariable(name, location);
}

// Push loop statement node in stack
void DriverImpl::pushLoop(LoopNode* loopStatement) {
    m_loopStack.push(loopStatement);
}

// Pop loop statement node from stack
LoopNode* DriverImpl::popLoop() {
    kiwi_assert(!m_loopStack.empty() && "Scope stack is empty");
    LoopNode* loop = m_loopStack.top();
    m_loopStack.pop();
    return loop;
}

// Peak loop statement node from stack
LoopNode* DriverImpl::peakLoop() {
    if (m_loopStack.empty()) {
        return 0;
    }
    return m_loopStack.top();
}