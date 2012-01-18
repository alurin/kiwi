/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_DRIVER
#define KIWI_SCRIPT_DRIVER

#include "kiwi/String.hpp"
#include "kiwi/Engine.hpp"
#include "kiwi/Script/RootNode.hpp"

namespace kiwi {
    namespace script {
        /**
         * Class for language analysis driver
         *
         * @since 0.1
         * @todo Error handling
         */
        class KIWI_API Driver {
        public:
            //===----------------------------------------------------------------===//
            // Driver parse
            //===----------------------------------------------------------------===//

            /**
             * Parse file and return function for execute
             *
             * @return Root node of AST
             */
            static RootNode* parseFile(Engine* engine, const Path& filename);

            /**
             * Invoke the scanner and parser for a stream.
             *
             * @param in        input stream
             * @param sname     stream name for error messages
             * @return          Root node of AST if successfully parsed
             */
            static RootNode* parseStream(Engine* engine, std::istream& in,
                              const String& sname = "stream input");

            /**
             * Invoke the scanner and parser on an input string.
             * @param input     input string
             * @param sname     stream name for error messages
             * @return          true if successfully parsed
             */
            static RootNode* parseString(Engine* engine, const std::string& input,
                              const String& sname = "string stream");
            
            //===----------------------------------------------------------------===//
            // Driver debug
            //===----------------------------------------------------------------===//
            
            /// Driver in debug mode?
            static bool isDebugMode() {
                return s_debug;
            }
            
            /// Set driver debug mode
            static void setDebugMode(bool debug) {
                s_debug = debug;
            }
        private:
            /// Lexer and parser debug mode
            static bool s_debug;
        };
    }
}

#endif