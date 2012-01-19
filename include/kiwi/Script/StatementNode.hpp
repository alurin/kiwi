/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_STATEMENTNODE_HPP_INCLUDE
#define KIWI_SCRIPT_STATEMENTNODE_HPP_INCLUDE

#include "kiwi/Script/ExpressionNode.hpp"
#include <map>

namespace kiwi {
    namespace script {
        class StatementNode : public Node {
        public:

        protected:
            StatementNode(const Location& location);
        };

        /**
         * Statement variable node
         */
        class ExpressionStatementNode : public StatementNode {
        public:
            /// ExpressionStatementNode constructor
            ExpressionStatementNode(ExpressionNode* node);

            /// ExpressionStatementNode destructor
            virtual ~ExpressionStatementNode();

            /// Returns expression node
            ExpressionNode* getVariable() const {
                return m_node;
            }
        protected:
            /// Expression node
            ExpressionNode* m_node;
        };

        /**
         *  Variable scope statement node
         */
        class ScopeStatementNode : public StatementNode {
        public:
            /// Scope statement node constructor
            ScopeStatementNode(const Location& location);

            /// Scope statement node constructor
            ScopeStatementNode(ScopeStatementNode* parentScope, const Location& location);

            /// Scope statement node destructor
            virtual ~ScopeStatementNode();
        protected:
            /// Parent scope statement node
            ScopeStatementNode* m_parentScope;
        };

        /**
         * Statement variable node
         */
        class VariableNode : public Node {
        public:
            /// Variable node constructor
            VariableNode(const String& name, ScopeStatementNode* parentScope, const Location& location);
        protected:
            /// Variable name
            UnicodeString m_name;

            /// Variable owner statement
            ScopeStatementNode* m_parentScope;
        };

        /**
         * Variable left expression node
         */
        class LeftVariableNode : public LeftExpressionNode {
        public:
            /// Left variable node constructor
            LeftVariableNode(VariableNode* node, const Location& location);

            /// Returns variable node
            VariableNode* getVariable() const {
                return m_node;
            }
        protected:
            /// Variable node
            VariableNode* m_node;
        };

        /**
         * Variable right expression node
         */
        class RightVariableNode : public ExpressionNode {
        public:
            /// Right variable node constructor
            RightVariableNode(VariableNode* node, const Location& location);

            /// Returns variable node
            VariableNode* getVariable() const {
                return m_node;
            }
        protected:
            /// Variable node
            VariableNode* m_node;
        };
    }
}

#endif
