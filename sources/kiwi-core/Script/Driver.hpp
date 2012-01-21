/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_DRIVER_HPP_INCLUDED
#define	KIWI_SCRIPT_DRIVER_HPP_INCLUDED

#include "kiwi/Types.hpp"
#include "kiwi/Script/RootNode.hpp"
#include "kiwi/Script/StatementNode.hpp"
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
        class DriverImpl {
        public:
            /**
             * Driver constructor
             */
            DriverImpl(Engine* engine);

            /**
             * Destroy driver and clear all used symbols
             *
             * @todo Memory allocation and deallocation!!! Memory leak!!!!
             */
            virtual ~DriverImpl();

            /// Returns owner engine
            Engine* getEngine() const {
                return m_engine;
            }

            //===----------------------------------------------------------------===//
            // Driver debug & trace
            //===----------------------------------------------------------------===//

            /**
             * Invoke the scanner and parser for a stream.
             *
             * @param in        input stream
             * @param sname     stream name for error messages
             * @return          true if successfully parsed
             */
            RootNode* parseStream(std::istream& in,
                                    const String& sname = "stream input");

            //===----------------------------------------------------------------===//
            // Driver debug & trace
            //===----------------------------------------------------------------===//

            /// Get stream name
            String getStreamName() const {
                return m_streamName;
            }

            /// Returns stream name in utf-8 encoding
            Path getStreamNameUTF8() const;

            //===----------------------------------------------------------------===//
            // Methods for work with statement scopes stack
            //===----------------------------------------------------------------===//

            /// Push scope statement node in stack
            void pushScope(ScopeStatementNode* scopeStatement);

            /// Pop scope statement node from stack
            ScopeStatementNode* popScope();

            /// Peak scope statement node from stack
            ScopeStatementNode* peakScope();

            //===----------------------------------------------------------------===//
            // Methods for work with variables
            //===----------------------------------------------------------------===//

            /// Get variable for current scope
            VariableNode* getVariable(const String& name);

            /// Declare variable in current scope with default value
            VariableNode* declareVariable(const String& name, const Location& location);

            //===----------------------------------------------------------------===//
            // Methods for work with loops
            //===----------------------------------------------------------------===//

            /// Push loop statement node in stack
            void pushLoop(LoopNode* loopStatement);

            /// Pop loop statement node from stack
            LoopNode* popLoop();

            /// Peak loop statement node from stack
            LoopNode* peakLoop();

        protected:
            /// Owner engine
            Engine* m_engine;

            /// Stream name
            String m_streamName;

            /// Cached stream name in utf-8 encoding
            mutable Path m_streamNameUTF8;

            /// Current lexer
            Lexer* m_lexer;

            /// Scope statement stack
            std::stack<ScopeStatementNode*> m_scopeStack;

            /// Loop statement stack
            /// @todo How check loops on nested functions?
            std::stack<LoopNode*> m_loopStack;
        };
    }
}

#endif	/* DRIVER_HPP */
