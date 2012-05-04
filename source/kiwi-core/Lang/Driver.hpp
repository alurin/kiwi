/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef EXAMPLE_DRIVER_H
#define EXAMPLE_DRIVER_H

#include "kiwi/config.hpp"
#include "Factory.hpp"
#include <string>

/** The example namespace is used to encapsulate the three parser classes
 * example::Parser, example::Scanner and example::Driver */
namespace kiwi {
namespace lang {

    class FunctionNode;
    class ScopeNode;

    /** The Driver class brings together all components. It creates an instance of
     * the Parser and Scanner classes and connects them. Then the input stream is
     * fed into the scanner object and the parser gets it's token
     * sequence. Furthermore the driver object is available in the grammar rules as
     * a parameter. Therefore the driver class contains a reference to the
     * structure into which the parsed data is saved. */
    class Driver : public NodeFactory
    {
        friend class DriverRef;
    public:
        /// destructor
        virtual ~Driver();

        /// enable debug output in the flex scanner
        bool trace_scanning;

        /// enable debug output in the bison parser
        bool trace_parsing;

        /// stream name (file or input stream) used for error messages.
        std::string streamname;

        /// Invoke the scanner and parser for a stream.
        bool parse();
    public:
        // To demonstrate pure handling of parse errors, instead of
        // simply dumping them on the standard error output, we will pass
        // them to the driver using the following two member functions.

        /** Error handling with associated line number. This can be modified to
         * output the error e.g. to a dialog box. */
        void error(const class location& l, const std::string& m);

        /** General error handling. This can be modified to output the error
         * e.g. to a dialog box. */
        // void error(const std::string& m);

        /** Pointer to the current lexer instance, this is used to connect the
         * parser to the scanner. It is used in the yylex macro. */
        class Scanner* lexer;

    private:

        /// Pointer to input stream
        std::istream* m_stream;

        /// Driver has ownership for input stream
        bool m_hasOwnership;

        /// construct a new parser driver context
        Driver(ContextPtr context, TypePtr thisType, std::istream* stream,
                const std::string& sname, bool hasOwnership);

        /// Create driver for parsing a stream.
        static Driver* createFromStream(ContextPtr context, TypePtr thisType,
                std::istream& in, const std::string& sname = "stream input");

        /// Create driver for parsing a string.
        static Driver* createFromString(ContextPtr context, TypePtr thisType,
            const std::string& input, const std::string& sname = "string stream");

        /// Create driver for parsing a file.
        static Driver* createFromFile(ContextPtr context, TypePtr thisType, const std::string& filename);
    };

    /// Memory safe
    class DriverRef {
    public:
        /// Constructor
        DriverRef(ContextPtr context, TypePtr thisType);

        /// Destructor
        ~DriverRef();

        /// Create driver for parsing a stream.
        bool parseStream(
                std::istream& in, const std::string& sname = "stream input");

        /// Create driver for parsing a string.
        bool parseString(
            const std::string& input, const std::string& sname = "string stream");

        /// Create driver for parsing a file.
        bool parseFile( const std::string& filename);

        /// Return main method from current source file
        MethodPtr getMainMethod() const {
            return m_mainMethod;
        }
    private:
        Driver*     m_driver;
        ContextPtr  m_context;
        TypePtr     m_thisType;
        MethodPtr   m_mainMethod;

        // local parsing and building process
        bool parse();
    };

} // namespace lang
} // namespace kiwi

#endif // EXAMPLE_DRIVER_H
