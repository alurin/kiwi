#ifndef KIWI_LANG_EXPRESSIONNODE_INTERNAL
#define KIWI_LANG_EXPRESSIONNODE_INTERNAL

#include "Node.hpp"
#include "kiwi/Member.hpp"
#include "kiwi/Codegen/Expression.hpp"
#include "kiwi/Codegen/Variable.hpp"
#include <vector>

namespace kiwi {
    typedef boost::shared_ptr<class Context> ContextRef;

namespace lang {
    class VariableNode;
    class ArgumentNode;

    using codegen::ExpressionGen;
    using codegen::StatementGen;
    using codegen::VariableGen;

    class MutableNode : public Node {
    public:
        virtual ExpressionGen emit(const ExpressionGen& gen) =0;
    };

    class ExpressionNode : public Node {
    public:
        virtual ExpressionGen emit(const StatementGen& value) =0;
    };

    class BinaryNode : public ExpressionNode {
    public:

        BinaryNode(Member::BinaryOpcode opcode, ExpressionNode* left, ExpressionNode* right, bool logic = false);

        virtual ~BinaryNode();

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Member::BinaryOpcode    m_opcode;
        ExpressionNode*              m_left;
        ExpressionNode*              m_right;
        bool                    m_logic;
    };

    class UnaryNode : public ExpressionNode {
    public:
        UnaryNode(Member::UnaryOpcode opcode, ExpressionNode* value, bool post = false);

        virtual ~UnaryNode();

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Member::UnaryOpcode m_opcode;
        ExpressionNode*          m_value;
        bool                m_post;
    };

    class AssignNode : public ExpressionNode {
    public:
        AssignNode(MutableNode* left, ExpressionNode* right);

        virtual ~AssignNode();

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        MutableNode*   m_left;
        ExpressionNode*  m_right;
    };

    class ArgumentMutableNode : public MutableNode {
    public:
        ArgumentMutableNode(ArgumentNode* arg);

        /// emit instructions
        virtual ExpressionGen emit(const ExpressionGen& gen);
    protected:
        ArgumentNode* o_arg;
    };

    class ArgumentExpressionNode : public ExpressionNode {
    public:
        ArgumentExpressionNode(ArgumentNode* arg);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ArgumentNode* o_arg;
    };

    class VariableMutableNode : public MutableNode {
    public:
        VariableMutableNode(VariableNode* var);

        /// emit instructions
        virtual ExpressionGen emit(const ExpressionGen& gen);
    protected:
        VariableNode* o_var;
    };

    class VariableExpressionNode : public ExpressionNode {
    public:
        VariableExpressionNode(VariableNode* var);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        VariableNode* o_var;
    };

    class InstanceMutableNode : public MutableNode {
    public:
        InstanceMutableNode(const Identifier& name);

        /// emit instructions
        virtual ExpressionGen emit(const ExpressionGen& gen);
    protected:
        Identifier m_name;
    };

    class InstanceExpressionNode : public ExpressionNode {
    public:
        InstanceExpressionNode(const Identifier& name);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Identifier m_name;
    };

    class IntegerConstNode : public ExpressionNode
    {
    public:
        IntegerConstNode(ContextRef context, int32_t value);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ContextRef  m_context;
        int32_t     m_value;
    };

    class StringConstNode : public ExpressionNode
    {
    public:
        StringConstNode(ContextRef context, const String& value);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ContextRef  m_context;
        String      m_value;
    };

    class CharConstNode : public ExpressionNode
    {
    public:
        CharConstNode(ContextRef context, const UChar& value);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ContextRef  m_context;
        UChar     m_value;
    };

    class BoolConstNode : public ExpressionNode
    {
    public:
        BoolConstNode(ContextRef context, bool value);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        ContextRef  m_context;
        bool        m_value;
    };

    class CallNode : public ExpressionNode {
    public:
        CallNode(const Identifier& method);

        /// Add named argument
        void append(const Identifier& name, ExpressionNode* value);

        /// Add positior argument
        void append(ExpressionNode* value);

        /// emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        class CallArgument {
        public:
            ExpressionNode*  Value;
            int32_t     Position;
            Identifier  Name;
        };
    protected:
        Identifier                  m_method;
        std::vector<CallArgument>   m_arguments;
        bool                        m_hasNamed;
    };
}}

#endif
