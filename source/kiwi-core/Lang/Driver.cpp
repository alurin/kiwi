// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include "Driver.hpp"
#include "Logger.hpp"
#include "ExpressionNode.hpp"
#include "FunctionNode.hpp"
#include "kiwi/Context.hpp"
#include "scanner.h"
#include "TypeNode.hpp"
#include <fstream>
#include <sstream>

using namespace kiwi;
using namespace kiwi::lang;

Driver::Driver(Context* context, Type* thisType, std::istream* stream,
     const std::string& sname, bool hasOwnership)
: NodeFactory(context, thisType),
    m_stream(stream),
    logger(new SourceLogger(stream)),
    m_hasOwnership(hasOwnership),
    streamname(sname),
    trace_scanning(context->isDebug()),
    trace_parsing(context->isDebug()) {
}

Driver::~Driver() {
    if (m_hasOwnership) {
        delete m_stream;
    }
    delete logger;
}

Driver* Driver::createFromStream(Context* context, Type* thisType, std::istream& stream, const std::string& sname) {
    return new Driver(context, thisType, &stream, sname, false);
}

Driver* Driver::createFromFile(Context* context, Type* thisType, const std::string &filename) {
    std::ifstream* in = new std::ifstream(filename.c_str(), std::ios::binary | std::ios::in);
    if (!in->good()) {
        delete in;
        return 0;
    }
    return new Driver(context, thisType, in, filename, true);
}

Driver* Driver::createFromString(Context* context, Type* thisType, const std::string &input, const std::string& sname) {
    std::istringstream* iss = new std::istringstream(input);
    return new Driver(context, thisType, iss, sname, true);
}

bool Driver::parse() {
    /// prepare stream
    Scanner      scanner(m_stream);
    scanner.set_debug(trace_scanning);

    /// prepare lexer and loger
    this->lexer  = &scanner;

    /// parse stream
    Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

void Driver::error(const class location& l,
		   const std::string& m) {
    if (logger)
        logger->error(l, m);
}

DriverRef::DriverRef(Context* context, Type* thisType)
: m_context(context), m_thisType(thisType), m_driver(0) {
}

DriverRef::~DriverRef() {
    delete m_driver;
}

// Create driver for parsing a stream.
bool DriverRef::parseStream(std::istream& input, const std::string& sname) {
    m_driver = Driver::createFromStream(m_context, m_thisType, input, sname);
    return parse();
}

// Create driver for parsing a string.
bool DriverRef::parseString(const std::string& input, const std::string& sname) {
    m_driver = Driver::createFromString(m_context, m_thisType, input, sname);
    return parse();
}

// Create driver for parsing a file.
bool DriverRef::parseFile( const std::string& filename) {
    m_driver = Driver::createFromFile(m_context, m_thisType, filename);
    return parse();
}

bool DriverRef::parse() {
    if (!m_driver) {
        return false;
    }

    Driver& driver = *m_driver;
    if (driver.parse()) {
        for (std::vector<lang::FieldNode*>::const_iterator i = driver.field_begin(); i != driver.field_end(); ++i) {
            (*i)->generate(m_thisType);
        }

        /// Emit type structure
        m_thisType->emit();

        for (std::vector<lang::FunctionNode*>::const_iterator i = driver.func_begin(); i != driver.func_end(); ++i) {
            (*i)->generate(driver, m_thisType);
            if ((*i)->getName() == "main") {
                m_mainMethod = (*i)->getMethod();
            }
        }

        /// @todo build examples
        for (std::vector<lang::FunctionNode*>::const_iterator i = driver.func_begin(); i != driver.func_end(); ++i) {
            (*i)->emit(driver, m_thisType);
        }
    }
}
