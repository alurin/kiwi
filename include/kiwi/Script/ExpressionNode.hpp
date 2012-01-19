/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_SCRIPT_EXPRESSIONNODE_HPP_INCLUDED
#define KIWI_SCRIPT_EXPRESSIONNODE_HPP_INCLUDED

#include "kiwi/Script/Node.hpp"
#include "kiwi/Types.hpp"

namespace kiwi {
    namespace script {

        /**
         * The ExpressionNode class is abstract base for all right expressions nodes
         */
        class ExpressionNode : public Node {
        public:

        protected:
            /// Protected constructor for expressions
            ExpressionNode(const Location& location);
        };

        /**
         * The LeftExpressionNode class is abstract base for all left expressions nodes
         */
        class LeftExpressionNode : public Node {
        protected:
            /// Protected constructor for expressions
            LeftExpressionNode(const Location& location);
        };

        /**
         *
         */
        class UnaryExpressionNode : public ExpressionNode {
        public:
            /// Enumeration of unary expression node opcodes
            enum Opcode {
                OP_NOT = 0,
                OP_POS = 1,
                OP_NEG = 2
            };

            /// UnaryExpressionNode constructor
            UnaryExpressionNode(ExpressionNode* node, Opcode opcode, const Location& location);

            /// Virtual destructors
            virtual ~UnaryExpressionNode();

            /// Returns unary opcode
            Opcode getOpcode() const {
                return m_opcode;
            }

            /// Returns child node
            ExpressionNode* getNode() const {
                return m_node;
            }
        protected:
            /// Unary opcode
            Opcode m_opcode;

            /// Expression node
            ExpressionNode* m_node;
        };

        /**
         *
         */
        class BinaryExpressionNode : public ExpressionNode {
        public:
            /// Enumeration of binary expression node opcodes
            enum Opcode {
                OP_ADD = 0,
                OP_SUB = 1,
                OP_MUL = 2,
                OP_DIV = 3
            };

            /// BinaryExpressionNode constructor
            BinaryExpressionNode(ExpressionNode* leftNode, ExpressionNode* rightNode, Opcode opcode, const Location& location);

            /// Virtual destructors
            virtual ~BinaryExpressionNode();

            /// Returns binary opcode
            Opcode getOpcode() const {
                return m_opcode;
            }

            /// Returns left node
            ExpressionNode* getLeftNode() const {
                return m_leftNode;
            }

            /// Returns right node
            ExpressionNode* getRightNode() const {
                return m_rightNode;
            }
        protected:
            /// Binary opcode
            Opcode m_opcode;

            /// Expression left node
            ExpressionNode* m_leftNode;

            /// Expression right node
            ExpressionNode* m_rightNode;
        };

        /**
         *
         */
        class AssignmentExpressionNode : public ExpressionNode {
        public:
            /// BinaryExpressionNode constructor
            AssignmentExpressionNode(LeftExpressionNode* leftNode, ExpressionNode* rightNode, const Location& location);

            /// Virtual destructors
            virtual ~AssignmentExpressionNode();

            /// Returns left node
            LeftExpressionNode* getLeftNode() const {
                return m_leftNode;
            }

            /// Returns right node
            ExpressionNode* getRightNode() const {
                return m_rightNode;
            }
        protected:

            /// Expression left node
            LeftExpressionNode* m_leftNode;

            /// Expression right node
            ExpressionNode* m_rightNode;
        };


        /**
         * The ConstantNode class is abstract base for all constant nodes in AST
         *
         * @since 0.1
         */
        class ConstantNode  : public ExpressionNode {
        protected:
            /// Constant node constructor
            ConstantNode(const Location& location);
        };

        /**
         * The IntegerNode class is represents integer constant node in AST
         *
         * @since 0.1
         */
        class IntegerNode : public ConstantNode {
        public:
            /// IntegerNode constructor
            IntegerNode(int64_t value, const Location& location);

            /// Returns value
            int64_t getValue() const {
                return m_value;
            }
        protected:
            const int64_t m_value;
        };

        /**
         * The BooleanNode class is represents boolean constant node in AST
         *
         * @since 0.1
         */
        class BooleanNode : public ConstantNode {
        public:
            /// BooleanNode constructor
            BooleanNode(bool value, const Location& location);

            /// Returns value
            bool getValue() const {
                return m_value;
            }
        protected:
            const bool m_value;
        };

        /**
         * The StringNode class is represents string constant node in AST
         *
         * @since 0.1
         */
        class StringNode : public ConstantNode {
        public:
            /// StringNode constructor
            StringNode(const String& value, const Location& location);

            /// Returns value
            String getValue() const {
                return m_value;
            }
        protected:
            const String m_value;
        };

        /**
         * The CharNode class is represents char constant node in AST
         *
         * @since 0.1
         */
        class CharNode : public ConstantNode {
        public:
            /// CharNode constructor
            CharNode(UChar value, const Location& location);

            /// Returns value
            UChar getValue() const {
                return m_value;
            }
        protected:
            const UChar m_value;
        };

        /**
         * The NullableNode class is represents null constant node in AST
         *
         * @since 0.1
         */
        class NullableNode : public ConstantNode {
        public:
            /// NullableNode constructor
            NullableNode(const Location& location);
        };

    }
}

#endif