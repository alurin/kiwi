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
#include <vector>

namespace kiwi {
    namespace script {
        /**
         *
         */
        class StatementNode : public Node {
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

        class VariableNode;

        /**
         *  Variable scope statement node
         */
        class ScopeStatementNode : public StatementNode {
        public:
            /// Varaibles map type
            typedef std::map<String, VariableNode*> VariableMap;

            /// Varaibles map iterator type
            typedef VariableMap::iterator VariableIterator;

            /// Statement type
            typedef std::vector<StatementNode*> StatementList;

            /// Scope statement node constructor
            ScopeStatementNode(const Location& location);

            /// Scope statement node constructor
            ScopeStatementNode(ScopeStatementNode* parentScope, const Location& location);

            /// Scope statement node destructor
            virtual ~ScopeStatementNode();

            /// Get variable from scope
            VariableNode* getVariable(const String& name);

            /// Declare variable in current scope
            VariableNode* declareVariable(const String& name, const Location& location);

            /// Add statement ownership in scope
            void addStatement(StatementNode* statement);
        protected:
            /// Parent scope statement node
            ScopeStatementNode* m_parentScope;

            /// Varaibles map
            VariableMap m_variables;

            /// Statement list
            StatementList m_statements;
        };

        /**
         * Statement variable node
         */
        class VariableNode : public Node {
            friend VariableNode* ScopeStatementNode::declareVariable(const String&, const kiwi::script::Location&);
        public:
            /// Returns owner statement
            ScopeStatementNode* getParentScope() const {
                return m_parentScope;
            }
        protected:
            /// Variable name
            UnicodeString m_name;

            /// Variable owner statement
            ScopeStatementNode* m_parentScope;

            /// Variable node constructor
            VariableNode(const String& name, ScopeStatementNode* parentScope, const Location& location);
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

        /**
         * Logical statement node
         */
        class ConditionalStatementNode : public StatementNode {
        public:
            /// Logical statement node constructor
            ConditionalStatementNode(
                ExpressionNode* conditional,
                StatementNode* trueStatement,
                StatementNode* falseStatement,
                const Location& location);

            /// Logical statement node constructor
            ConditionalStatementNode(
                ExpressionNode* conditional,
                StatementNode* trueStatement,
                const Location& location);

            /// Logical statement node destructor
            ~ConditionalStatementNode();

            /// Returns conditional node
            ExpressionNode* getConditional() {
                return m_conditional;
            }

            /// Returns true statement node
            StatementNode* getTrueStatement() const {
                return m_trueStatement;
            }

            /// Returns false statement node
            StatementNode* getFalseStatement() const {
                return m_falseStatement;
            }
        protected:
            /// Conditional node
            ExpressionNode* m_conditional;

            /// Trus statement node
            StatementNode* m_trueStatement;

            /// False statement node
            StatementNode* m_falseStatement;
        };
    }
}

#endif
