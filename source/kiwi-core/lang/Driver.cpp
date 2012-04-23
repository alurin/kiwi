// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include "Driver.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "kiwi/Context.hpp"
#include "scanner.h"
#include "TypeNode.hpp"
#include <fstream>
#include <sstream>

using namespace kiwi;
using namespace kiwi::lang;

Driver::Driver(Context* context, Type* thisType)
    : NodeFactory(context, thisType),
      trace_scanning(context->isDebug()),
      trace_parsing(context->isDebug())
{
}

NodeFactory::~NodeFactory()
{
    for (std::vector<FieldNode*>::const_iterator i = field_begin(); i != field_end(); ++i) {
        FieldNode* node = *i;
        delete node;
    }

    for (std::vector<FunctionNode*>::const_iterator i = func_begin(); i != func_end(); ++i) {
        FunctionNode* node = *i;
        delete node;
    }
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
