/*
 *******************************************************************************
 *   Copyright (C) 2010 Kiwi Developers Group
 *   All Rights Reserved.
 *******************************************************************************
 */
/**
 * @file
 * @brief
 */
#ifndef KIWI_SCRIPT_DRIVER_HPP_INCLUDED
#define	KIWI_SCRIPT_DRIVER_HPP_INCLUDED

#include "kiwi/String.hpp"
#include <stack>
#include <string>
#include <vector>

namespace kiwi {
    class Engine;

    namespace script {
        class Lexer;

        /**
         * Class for instance of language analyse driver
         *
         * @since 0.1
         * @todo Error handling
         */
        class KIWI_LOCAL Driver {
        public:
            /// Driver constructor
            Driver(Engine* engine);

            /// Destroy driver and clear all used symbols
            ///
            /// @todo Memory allocation and deallocation!!! Memory leak!!!!
            virtual ~Driver();

            //===----------------------------------------------------------------===//
            // Driver debug & trace
            //===----------------------------------------------------------------===//

            /// Parse file and return function for execute
            bool parseFile(const Path& filename);

            /** Invoke the scanner and parser for a stream.
             * @param in        input stream
             * @param sname     stream name for error messages
             * @return          true if successfully parsed
             */
            bool parseStream(std::istream& in,
                              const String& sname = "stream input");

            /** Invoke the scanner and parser on an input string.
             * @param input     input string
             * @param sname     stream name for error messages
             * @return          true if successfully parsed
             */
            bool parseString(const std::string& input,
                              const String& sname = "string stream");

            /** General error handling. This can be modified to output the error
             * e.g. to a dialog box. */

            //===----------------------------------------------------------------===//
            // Driver debug & trace
            //===----------------------------------------------------------------===//

            /// Driver in debug mode?
            bool isDebug() const {
                return KIWI_DEBUG;
            }

            /// Get stream name
            String getStreamName() const {
                return m_streamName;
            }

            /// Returns stream name in utf-8 encoding
            Path getStreamNameUTF8() const;
        protected:
            /// Stream name
            String m_streamName;
            
            /// Cached stream name in utf-8 encoding
            mutable Path m_streamNameUTF8;

            /// Current lexer
            Lexer* m_lexer;
        };
    }
}

#endif	/* DRIVER_HPP */
