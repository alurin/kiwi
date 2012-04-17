// $Id: driver.h 17 2007-08-19 18:51:39Z tb $
/** \file driver.h Declaration of the kiwi::lang::Driver class. */

#ifndef EXAMPLE_DRIVER_H
#define EXAMPLE_DRIVER_H

#include "kiwi/Config.hpp"
#include <string>
#include <vector>
#include <stack>

/** The example namespace is used to encapsulate the three parser classes
 * example::Parser, example::Scanner and example::Driver */
namespace kiwi {
namespace lang {

class FunctionNode;
class TypeFactory;
class TypeNode;
class ExpressionFactory;
class ScopeNode;

/** The Driver class brings together all components. It creates an instance of
 * the Parser and Scanner classes and connects them. Then the input stream is
 * fed into the scanner object and the parser gets it's token
 * sequence. Furthermore the driver object is available in the grammar rules as
 * a parameter. Therefore the driver class contains a reference to the
 * structure into which the parsed data is saved. */
class Driver
{
public:
    enum Mode {
        MODE_SCRIPT     = 0,
        MODE_INLINE     = 1,
        MODE_COMPONENT  = 2
    }; // enum Mode

    /// construct a new parser driver context
    Driver();

    /// set mode
    void setMode(Mode mode) {
        m_mode = mode;
    }

    /// returns mode
    Mode getMode() const {
        return m_mode;
    }

    /// returns types factory
    TypeFactory* type();

    /// returns expressions factory
    ExpressionFactory* expr();

    /// returns current function
    FunctionNode* func();

    /// declare function
    FunctionNode* func(const Identifier& name, TypeNode* type);

    /// end current function
    FunctionNode* funcEnd();

    /// returns current scope
    ScopeNode* scope();

    /// begin new scope
    ScopeNode* scopeBegin();

    /// end current scope
    ScopeNode* scopeEnd();

    std::vector<FunctionNode*>::const_iterator func_begin() const
    {
        return m_functions.begin();
    }

    std::vector<FunctionNode*>::const_iterator func_end() const
    {
        return m_functions.end();
    }
public:
    /// enable debug output in the flex scanner
    bool trace_scanning;

    /// enable debug output in the bison parser
    bool trace_parsing;

    /// stream name (file or input stream) used for error messages.
    std::string streamname;

    /** Invoke the scanner and parser for a stream.
     * @param in	input stream
     * @param sname	stream name for error messages
     * @return		true if successfully parsed
     */
    bool parseStream(std::istream& in,
		      const std::string& sname = "stream input");

    /** Invoke the scanner and parser on an input string.
     * @param input	input string
     * @param sname	stream name for error messages
     * @return		true if successfully parsed
     */
    bool parseString(const std::string& input,
		      const std::string& sname = "string stream");

    /** Invoke the scanner and parser on a file. Use parse_stream with a
     * std::ifstream if detection of file reading errors is required.
     * @param filename	input file name
     * @return		true if successfully parsed
     */
    bool parseFile(const std::string& filename);

public:
    // To demonstrate pure handling of parse errors, instead of
    // simply dumping them on the standard error output, we will pass
    // them to the driver using the following two member functions.

    /** Error handling with associated line number. This can be modified to
     * output the error e.g. to a dialog box. */
    void error(const class location& l, const std::string& m);

    /** General error handling. This can be modified to output the error
     * e.g. to a dialog box. */
    void error(const std::string& m);

    /** Pointer to the current lexer instance, this is used to connect the
     * parser to the scanner. It is used in the yylex macro. */
    class Scanner* lexer;
protected:
    std::stack<FunctionNode*>   m_funcs;
    std::stack<ScopeNode*>      m_scopes;
    std::vector<FunctionNode*>  m_functions;
    Mode m_mode;
};

} // namespace lang
} // namespace kiwi

#endif // EXAMPLE_DRIVER_H
