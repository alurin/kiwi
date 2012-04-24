#include "Factory.hpp"
#include "kiwi/Support/Cast.hpp"
#include <assert.h>

using namespace kiwi;
using namespace kiwi::lang;

NodeFactory::NodeFactory(Context* context, Type* thisType)
: m_context(context), m_this(thisType) {

}

/// @todo clear stacks!!!!
NodeFactory::~NodeFactory() {
    for (std::vector<CompoundNode*>::const_iterator i = m_compounds.begin(); i != m_compounds.end(); ++i) {
        CompoundNode* node = *i;
        delete node;
    }
}

Module* NodeFactory::getModule() const {
    return m_this->getModule();
}

void NodeFactory::prepareScript(const location& loc) {
    /// add file level class
    CompoundNode* current = new ConcreteClassType(m_this);
    current->setLocation(loc);
    m_classes.push(current);
    m_compounds.push_back(current);

    /// add file level function. This is not worked in current versions of parser
    // FunctionNode* func = new FunctionNode("main", new ConcreteTypeNode(m_this), createVoidTy(loc));
    // func->setLocation(loc);
    // m_funcs.push(func);
    // m_scopes.push(func->getRoot());
    // current->append(func);
}

CompoundNode* NodeFactory::classTop() {
    assert(!m_classes.empty() && "Classes stack is empty");
    return m_classes.top();
}

CompoundNode* NodeFactory::classBegin(const Identifier& name, const location& loc) {
    ClassNode* compound = new ClassNode(name);
    m_classes.push(compound);
    return compound;
}

CompoundNode* NodeFactory::classEnd() {
    assert(!m_classes.empty() && "Classes stack is empty");
    CompoundNode* compound = m_classes.top();
    m_classes.pop();
    m_compounds.push_back(compound);
    return compound;
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
    return func;
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

// returns current subtraction
SubtractionNode* NodeFactory::sub() {
    assert(!m_subs.empty() && "Subtractions stack is empty");
    return m_subs.top();
}

// begin new subtraction
SubtractionNode* NodeFactory::subBegin(ExpressionNode* expr) {
    SubtractionNode* sub = new SubtractionNode(expr);
    m_subs.push(sub);
    return sub;
}

// end current subtraction
SubtractionNode* NodeFactory::subEnd(const location& loc) {
    assert(!m_subs.empty() && "Subtractions stack is empty");
    SubtractionNode* sub = m_subs.top();
    sub->setLocation(loc);
    m_subs.pop();
    return sub;
}
