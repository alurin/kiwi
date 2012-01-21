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
        class StatementVisitor;

        /**
         *
         */
        class StatementNode : public Node {
        public:
            /// Accept method for visitor
            virtual void accept(StatementVisitor& visitor) =0;

            /// Accept visitor
            void accept(NodeVisitor& visitor); // virtual
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
            ExpressionNode* getChildNode() const {
                return m_node;
            }

            /// Accept visitor
            void accept(StatementVisitor& visitor); // virtual
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
            typedef VariableMap::const_iterator VariableIterator;

            /// Statement list type
            typedef std::vector<StatementNode*> StatementList;

            /// Statement list iterator type
            typedef StatementList::const_iterator StatementIterator;

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

            /// Accept visitor
            void accept(StatementVisitor& visitor); // virtual

            /// Return iterator pointed to begin of variables map
            VariableIterator var_begin() const {
                return m_variables.begin();
            }

            /// Return iterator pointed to end of variables map
            VariableIterator var_end() const {
                return m_variables.end();
            }

            /// Returns count of variables
            size_t var_size() const {
                return m_variables.size();
            }

            /// Return iterator pointed to begin of statements list
            StatementIterator stmt_begin() const {
                return m_statements.begin();
            }

            /// Return iterator pointed to end of statements list
            StatementIterator stmt_end() const {
                return m_statements.end();
            }

            /// Returns count of statements
            size_t stmt_size() const {
                return m_statements.size();
            }
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
            /// Returns name
            String getName() const {
                return m_name;
            }

            /// Returns owner statement
            ScopeStatementNode* getParentScope() const {
                return m_parentScope;
            }

            /// Accept visitor
            void accept(NodeVisitor& visitor); // virtual
        protected:
            /// Variable name
            String m_name;

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

            /// Accept visitor
            void accept(LeftExpressionVisitor& visitor); //virtual
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

            /// Accept visitor
            void accept(ExpressionVisitor& visitor); //virtual
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

            /// Accept visitor
            void accept(StatementVisitor& visitor); // virtual
        protected:
            /// Conditional node
            ExpressionNode* m_conditional;

            /// Trus statement node
            StatementNode* m_trueStatement;

            /// False statement node
            StatementNode* m_falseStatement;
        };

        /**
         * Abstract class for all loop statement nodes
         */
        class LoopNode : public StatementNode {
        public:
            /// Curcle node destructor
            virtual ~LoopNode();

            /// Returns child statement
            StatementNode* getStatement() const {
                return m_statementNode;
            }

            /// Set child statement and request ownership
            void setStatement(StatementNode* statement) {
                m_statementNode = statement;
            }

            /// Returns parent loop
            LoopNode* getParentLoop() const {
                return m_parentLoop;
            }

            /// Returns loop level
            int32_t getLevel() const {
                return m_level;
            }
        protected:
            /// Statement for loop
            StatementNode* m_statementNode;

            /// Parent loop
            LoopNode* m_parentLoop;

            /// Loop level
            int32_t m_level;

            /// Loop statement constructor
            LoopNode(LoopNode* parentLoop, const Location& location);

            /// Loop statement constructor
            LoopNode(StatementNode* statementNode, LoopNode* parentLoop, const Location& location);
        };

        /**
         *
         */
        class ConditionLoopNode : public LoopNode {
        public:
            /// Enumeration for position of conditional
            enum CheckPosition {
                PRE,
                POST
            };

            /// Conditional loop node constructor
            ConditionLoopNode(CheckPosition position, LoopNode* parentLoop, const Location& location);

            /// Conditional loop node constructor
            ConditionLoopNode(ExpressionNode* conditional, CheckPosition position, LoopNode* parentLoop, const Location& location);

            /// Conditional loop node destructor
            ~ConditionLoopNode();

            /// Returns conditional node
            ExpressionNode* getConditional() const {
                return m_conditional;
            }

            /// Set conditional node
            void setConditional(ExpressionNode* conditional) {
                m_conditional = conditional;
            }

            /// Returns position of conditional
            CheckPosition getPosition() const {
                return m_position;
            }

            /// Accept visitor
            void accept(StatementVisitor& visitor); // virtual
        protected:
            /// Conditional node
            ExpressionNode* m_conditional;

            /// Position of conditional
            CheckPosition m_position;
        };
    }
}

#endif
