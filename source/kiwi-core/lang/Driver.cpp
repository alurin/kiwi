// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include <fstream>
#include <sstream>

#include "Driver.hpp"
#include "FunctionNode.hpp"
#include "TypeNode.hpp"
#include "ExpressionNode.hpp"
#include "scanner.h"

using namespace kiwi;
using namespace kiwi::lang;

Driver::Driver(ContextRef context)
    : trace_scanning(false),
      trace_parsing(false),
      m_context(context)
{
}

bool Driver::parseStream(std::istream& in, const std::string& sname)
{
    streamname = sname;

    Scanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool Driver::parseFile(const std::string &filename)
{
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    return parseStream(in, filename);
}

bool Driver::parseString(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parseStream(iss, sname);
}

void Driver::error(const class location& l,
		   const std::string& m)
{
    std::cerr << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}

TypeFactory* Driver::type()
{
    /// @todo Memoty leak
    return new TypeFactory(m_context);
}

ExpressionFactory* Driver::expr()
{
    /// @todo Memoty leak
    return new ExpressionFactory();
}

FunctionNode* Driver::func()
{
    //assert(!m_funcs.empty() && "Functions stack is empty");
    return m_funcs.top();
}

FunctionNode* Driver::func(const Identifier& name, TypeNode* type)
{
    FunctionNode* func = new FunctionNode(name, type);
    m_funcs.push(func);
    m_scopes.push(func->getRoot());
    return func;
}

FunctionNode* Driver::funcEnd()
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
ScopeNode* Driver::scope()
{
    //assert(!m_scopes.empty() && "Scopes stack is empty");
    return m_scopes.top();
}

// begin new scope
ScopeNode* Driver::scopeBegin()
{
    ScopeNode* parent = scope();
    ScopeNode* scope  = new ScopeNode(parent);
    m_scopes.push(scope);
    return scope;
}

// end current scope
ScopeNode* Driver::scopeEnd()
{
    //assert(!m_scopes.empty() && "Scopes stack is empty");
    ScopeNode* scope = m_scopes.top();
    m_scopes.pop();
    return scope;
}