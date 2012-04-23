#include "Factory.hpp"
#include "kiwi/Support/Cast.hpp"
#include <assert.h>

using namespace kiwi;
using namespace kiwi::lang;

NodeFactory::~NodeFactory() {
    for (std::vector<FieldNode*>::const_iterator i = field_begin(); i != field_end(); ++i) {
        FieldNode* node = *i;
        delete node;
    }

    for (std::vector<FunctionNode*>::const_iterator i = func_begin(); i != func_end(); ++i) {
        FunctionNode* node = *i;
        delete node;
    }
}


FunctionNode* NodeFactory::func() {
    assert(!m_funcs.empty() && "Functions stack is empty");
    return m_funcs.top();
}

FunctionNode* NodeFactory::func(const Identifier& name, TypeNode* type) {
    FunctionNode* func = new FunctionNode(name, new ConcreteTypeNode(m_this), type);
    m_funcs.push(func);
    m_scopes.push(func->getRoot());
    return func;
}

FunctionNode* NodeFactory::funcEnd() {
    assert(!m_funcs.empty() && "Functions stack is empty");
    FunctionNode* func = m_funcs.top();
    m_funcs.pop();
    m_scopes.pop();
    if (m_funcs.empty()) {
        m_functions.push_back(func);
    }
    return func;
}

FieldNode* NodeFactory::field(const Identifier& name, TypeNode* type) {
    FieldNode* field = new FieldNode(name, type);
    m_fields.push_back(field);
    return field;
}

// returns current scope
ScopeNode* NodeFactory::scope() {
    assert(!m_scopes.empty() && "Scopes stack is empty");
    return m_scopes.top();
}

// begin new scope
ScopeNode* NodeFactory::scopeBegin() {
    ScopeNode* parent = scope();
    ScopeNode* scope  = new ScopeNode(parent);
    m_scopes.push(scope);
    return scope;
}

// end current scope
ScopeNode* NodeFactory::scopeEnd() {
    assert(!m_scopes.empty() && "Scopes stack is empty");
    ScopeNode* scope = m_scopes.top();
    m_scopes.pop();
    return scope;
}

MutableNode* NodeFactory::left(const Identifier& name, const location& loc) {
    MutableNode* node = scope()->get(name)->getLeft();
    node->setLocation(loc);
    return node;
}
ExpressionNode* NodeFactory::right(const Identifier& name, const location& loc) {
    ExpressionNode* node = scope()->get(name)->getRight();
    node->setLocation(loc);
    return node;
}

/// returns current call
CallNode* NodeFactory::call() {
    assert(!m_calls.empty() && "Calls stack is empty");
    return m_calls.top();
}

/// declare call
CallNode* NodeFactory::call(const Identifier& name, const location& loc) {
    assert(!m_calls.empty() && "Calls stack is empty");
    CallNode* call = new CallNode(new ThisNode(dyn_cast<ObjectType>(m_this)), name);
    call->setLocation(loc);
    m_calls.push(call);
    return call;
}

/// declare call
CallNode* NodeFactory::call(ExpressionNode* expr, const Identifier& name, const location& loc) {
    CallNode* call = new CallNode(expr, name);
    call->setLocation(loc);
    m_calls.push(call);
    return call;
}

/// declare call
CallNode* NodeFactory::call(ExpressionNode* expr, const location& loc) {
    CallNode* call = new CallNode(expr);
    call->setLocation(loc);
    m_calls.push(call);
    return call;
}

/// end current call
CallNode* NodeFactory::callEnd() {
    assert(!m_calls.empty() && "Calls stack is empty");
    CallNode* call = m_calls.top();
    m_calls.pop();
    return call;
}

ExpressionNode* NodeFactory::createThis(const location& loc) {
    ExpressionNode* node = new ThisNode(dyn_cast<ObjectType>(m_this));
    node->setLocation(loc);
    return node;
}
