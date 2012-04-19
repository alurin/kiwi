#ifndef KIWI_LANG_EXPRESSIONNODE_INTERNAL
#define KIWI_LANG_EXPRESSIONNODE_INTERNAL

#include "Node.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/codegen/Expression.hpp"
#include "kiwi/codegen/Variable.hpp"

namespace kiwi {
    typedef boost::shared_ptr<class Context> ContextRef;

namespace lang {
    class VariableNode;
    class ArgumentNode;

    using codegen::ExpressionGen;
    using codegen::StatementGen;
    using codegen::VariableGen;

    class LeftNode : public Node {
    public:
        virtual ExpressionGen emit(const ExpressionGen& gen) =0;
    };

    class RightNode : public Node {
    public:
        virtual ExpressionGen emit(const StatementGen& value) =0;
    };

    class BinaryNode : public RightNode {
    public:
        typedef BinaryOperator::Opcode Opcode;

        BinaryNode(Opcode opcode, RightNode* left, RightNode* right, bool logic = false);

        virtual ~BinaryNode();

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Opcode      m_opcode;
        RightNode*  m_left;
        RightNode*  m_right;
        bool        m_logic;
    };

    class UnaryNode : public RightNode {
    public:
        typedef UnaryOperator::Opcode Opcode;

        UnaryNode(Opcode opcode, RightNode* value, bool post = false);

        virtual ~UnaryNode();

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Opcode      m_opcode;
        RightNode*  m_value;
        bool        m_post;
    };

    class AssignNode : public RightNode {
    public:
        AssignNode(LeftNode* left, RightNode* right);

        virtual ~AssignNode();

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        LeftNode*   m_left;
        RightNode*  m_right;
    };

    class ArgumentLeftNode : public LeftNode {
    public:
        ArgumentLeftNode(ArgumentNode* arg);

        /// emit instructions
        virtual ExpressionGen emit(const ExpressionGen& gen);
    protected:
        ArgumentNode* o_arg;
    };

    class ArgumentRightNode : public RightNode {
    public:
        ArgumentRightNode(ArgumentNode* arg);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ArgumentNode* o_arg;
    };

    class VariableLeftNode : public LeftNode {
    public:
        VariableLeftNode(VariableNode* var);

        /// emit instructions
        virtual ExpressionGen emit(const ExpressionGen& gen);
    protected:
        VariableNode* o_var;
    };

    class VariableRightNode : public RightNode {
    public:
        VariableRightNode(VariableNode* var);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        VariableNode* o_var;
    };

    class IntegerConstNode : public RightNode
    {
    public:
        IntegerConstNode(ContextRef context, int32_t value);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ContextRef  m_context;
        int32_t     m_value;
    };

    class StringConstNode : public RightNode
    {
    public:
        StringConstNode(ContextRef context, const String& value);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ContextRef  m_context;
        String      m_value;
    };

    class CharConstNode : public RightNode
    {
    public:
        CharConstNode(ContextRef context, const UChar& value);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ContextRef  m_context;
        UChar     m_value;
    };
}}

#endif