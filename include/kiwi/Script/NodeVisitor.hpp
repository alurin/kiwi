#ifndef KIWI_SCRIPT_NODEVISITOR_HPP_INCLUDED
#define KIWI_SCRIPT_NODEVISITOR_HPP_INCLUDED

namespace kiwi {
    namespace script {
        class ExpressionNode;
        class LeftExpressionNode;
        class StatementNode;
        class UnaryExpressionNode;
        class BinaryExpressionNode;
        class AssignmentExpressionNode;
        class IntegerNode;
        class BooleanNode;
        class StringNode;
        class CharNode;
        class NullableNode;
        class RightVariableNode;
        class LeftVariableNode;
        class ExpressionStatementNode;
        class ScopeStatementNode;
        class ConditionalStatementNode;
        class ConditionLoopNode;
        class VariableNode;

        class NodeVisitor {
        public:
            /// Visit expression expression node
            virtual void visit(ExpressionNode* node) =0;

            /// Visit expression expression node
            virtual void visit(LeftExpressionNode* node) =0;

            /// Visit statement node
            virtual void visit(StatementNode* node) =0;

            /// Visit variable node
            virtual void visit(VariableNode* node) =0;
        };

        class ExpressionVisitor {
        public:
            /// Visit unary expression node
            virtual void visit(UnaryExpressionNode* node) =0;

            /// Visit binary expression node
            virtual void visit(BinaryExpressionNode* node) =0;

            /// Visit assignment expression node
            virtual void visit(AssignmentExpressionNode* node) =0;

            /// Visit integer node
            virtual void visit(IntegerNode* node) =0;

            /// Visit boolean node
            virtual void visit(BooleanNode* node) =0;

            /// Visit string node
            virtual void visit(StringNode* node) =0;

            /// Visit char node
            virtual void visit(CharNode* node) =0;

            /// Visit nullable node
            virtual void visit(NullableNode* node) =0;

            /// Visit variable node
            virtual void visit(RightVariableNode* node) =0;
        };

        class LeftExpressionVisitor {
        public:
            /// Visit variable node
            virtual void visit(LeftVariableNode* node) =0;
        };

        class StatementVisitor {
        public:
            /// Visit expression statement node
            virtual void visit(ExpressionStatementNode* node) =0;

            /// Visit scope statement node
            virtual void visit(ScopeStatementNode* node) =0;

            /// Visit conditional statement node
            virtual void visit(ConditionalStatementNode* node) =0;

            /// Visit condition loop node
            virtual void visit(ConditionLoopNode* node) =0;
        };

    }
}

#endif