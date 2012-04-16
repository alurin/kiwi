// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include <fstream>
#include <sstream>

#include "Driver.hpp"
#include "scanner.h"

namespace example {

Driver::Driver(class CalcContext& _calc)
    : trace_scanning(false),
      trace_parsing(false),
      calc(_calc)
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

} // namespace example
