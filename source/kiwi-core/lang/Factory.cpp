#include "Factory.hpp"

using namespace kiwi;
using namespace kiwi::lang;

FunctionNode* NodeFactory::func()
{
    //assert(!m_funcs.empty() && "Functions stack is empty");
    return m_funcs.top();
}

FunctionNode* NodeFactory::func(const Identifier& name, TypeNode* type)
{
    FunctionNode* func = new FunctionNode(name, type);
    m_funcs.push(func);
    m_scopes.push(func->getRoot());
    return func;
}

FunctionNode* NodeFactory::funcEnd()
{
    //assert(!m_funcs.empty() && "Functions stack is empty");
    FunctionNode* func = m_funcs.top();
    m_funcs.pop();
    m_scopes.pop();
    if (m_funcs.empty()) {
        m_functions.push_back(func);
    }
    return func;
}

// returns current scope
ScopeNode* NodeFactory::scope()
{
    //assert(!m_scopes.empty() && "Scopes stack is empty");
    return m_scopes.top();
}

// begin new scope
ScopeNode* NodeFactory::scopeBegin()
{
    ScopeNode* parent = scope();
    ScopeNode* scope  = new ScopeNode(parent);
    m_scopes.push(scope);
    return scope;
}

// end current scope
ScopeNode* NodeFactory::scopeEnd()
{
    //assert(!m_scopes.empty() && "Scopes stack is empty");
    ScopeNode* scope = m_scopes.top();
    m_scopes.pop();
    return scope;
}

LeftNode* NodeFactory::left(const Identifier& name, const location& loc)
{
    LeftNode* node = scope()->get(name)->getLeft();
    node->setLocation(loc);
    return node;
}
RightNode* NodeFactory::right(const Identifier& name, const location& loc)
{
    RightNode* node = scope()->get(name)->getRight();
    node->setLocation(loc);
    return node;
}

/// returns current call
CallNode* NodeFactory::call()
{
    //assert(!m_calls.empty() && "Calls stack is empty");
    return m_calls.top();
}

/// declare call
CallNode* NodeFactory::call(const Identifier& name)
{
    //assert(!m_calls.empty() && "Calls stack is empty");
    CallNode* call = new CallNode(name);
    m_calls.push(call);
    return call;
}

/// end current call
CallNode* NodeFactory::callEnd()
{
    //assert(!m_calls.empty() && "Calls stack is empty");
    CallNode* call = m_calls.top();
    m_calls.pop();
    return call;
}
