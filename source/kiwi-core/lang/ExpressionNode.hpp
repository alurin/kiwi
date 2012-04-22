#ifndef KIWI_LANG_EXPRESSIONNODE_INTERNAL
#define KIWI_LANG_EXPRESSIONNODE_INTERNAL

#include "Node.hpp"
#include "kiwi/Member.hpp"
#include "kiwi/Codegen/Expression.hpp"
#include "kiwi/Codegen/Variable.hpp"
#include <vector>

namespace kiwi {
    class Context;

namespace lang {
    class VariableNode;
    class ArgumentNode;

    using codegen::ExpressionGen;
    using codegen::StatementGen;
    using codegen::VariableGen;

    //==--------------------------------------------------------------------==//
    /// Mutable synatax node
    class MutableNode : public Node {
    public:
        /// Emit instructions for store value
        virtual ExpressionGen emit(const ExpressionGen& gen) =0;
    };

    //==--------------------------------------------------------------------==//
    /// Expression syntax node
    class ExpressionNode : public Node {
    public:
        /// Emit instruction for receive value
        virtual ExpressionGen emit(const StatementGen& value) =0;
    };

    //==--------------------------------------------------------------------==//
    /// Binary expression syntax node
    class BinaryNode : public ExpressionNode {
    public:
        /// Constructor
        BinaryNode(Member::BinaryOpcode opcode, ExpressionNode* left, ExpressionNode* right, bool logic = false);

        /// Destructor
        virtual ~BinaryNode();

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        /// Binary operation opcode
        Member::BinaryOpcode m_opcode;

        /// Left expression
        ExpressionNode* m_left;

        /// Right expression
        ExpressionNode* m_right;

        // Binary operator (`and` or `or`) is logic?
        bool m_logic;
    };

    //==--------------------------------------------------------------------==//
    /// Unary expression syntax node
    class UnaryNode : public ExpressionNode {
    public:
        /// Constructor
        UnaryNode(Member::UnaryOpcode opcode, ExpressionNode* value, bool post = false);

        /// Destructor
        virtual ~UnaryNode();

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        /// Unary operation opcode
        Member::UnaryOpcode m_opcode;

        /// Expression child value
        ExpressionNode* m_value;

        /// Post expression
        /// @todo Remove. ++ -- is operators for mutable expressions
        bool m_post;
    };

    //==--------------------------------------------------------------------==//
    /// Assing syntax node
    class AssignNode : public ExpressionNode {
    public:
        /// Constructor
        AssignNode(MutableNode* left, ExpressionNode* right);

        /// Destructor
        virtual ~AssignNode();

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        /// Left expression node
        MutableNode* m_left;

        /// Right expression node
        ExpressionNode* m_right;
    };

    //==--------------------------------------------------------------------==//
    /// Argument mutable syntax node
    class ArgumentMutableNode : public MutableNode {
    public:
        /// Constructor
        ArgumentMutableNode(ArgumentNode* arg);

        /// Emit instructions
        virtual ExpressionGen emit(const ExpressionGen& gen);
    protected:
        /// Argument node
        ArgumentNode* o_arg;
    };

    //==--------------------------------------------------------------------==//
    /// Argument expression syntax node
    class ArgumentExpressionNode : public ExpressionNode {
    public:
        /// Constructor
        ArgumentExpressionNode(ArgumentNode* arg);

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        /// Argument node
        ArgumentNode* o_arg;
    };

    //==--------------------------------------------------------------------==//
    /// Varaible mutable syntax node
    class VariableMutableNode : public MutableNode {
    public:
        /// Constructor
        VariableMutableNode(VariableNode* var);

        /// Emit instructions
        virtual ExpressionGen emit(const ExpressionGen& gen);
    protected:
        /// Varaible node
        VariableNode* o_var;
    };

    //==--------------------------------------------------------------------==//
    /// Varaible expression syntax node
    class VariableExpressionNode : public ExpressionNode {
    public:
        /// Constructor
        VariableExpressionNode(VariableNode* var);

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        /// Varaible node
        VariableNode* o_var;
    };

    /// TODO: ADD COMMETS ====================================================//
    class InstanceMutableNode : public MutableNode {
    public:
        InstanceMutableNode(const Identifier& name);

        /// Emit instructions
        virtual ExpressionGen emit(const ExpressionGen& gen);
    protected:
        Identifier m_name;
    };

    class InstanceExpressionNode : public ExpressionNode {
    public:
        InstanceExpressionNode(const Identifier& name);

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Identifier m_name;
    };

    class IntegerConstNode : public ExpressionNode
    {
    public:
        IntegerConstNode(Context* context, int32_t value);

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Context*  m_context;
        int32_t     m_value;
    };

    class StringConstNode : public ExpressionNode
    {
    public:
        StringConstNode(Context* context, const String& value);

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Context*  m_context;
        String      m_value;
    };

    class CharConstNode : public ExpressionNode
    {
    public:
        CharConstNode(Context* context, const UChar& value);

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Context*  m_context;
        UChar     m_value;
    };

    class BoolConstNode : public ExpressionNode
    {
    public:
        BoolConstNode(Context* context, bool value);

        /// Emit instructions
        virtual ExpressionGen emit(const StatementGen& gen);
    protected:
        Context*  m_context;
        bool        m_value;
    };

    class CallNode : public ExpressionNode {
    public:
        CallNode(const Identifier& method);

        /// Add named argument
        void append(const Identifier& name, ExpressionNode* value);

        /// Add positior argument
        void append(ExpressionNode* value);

        /// Emit instructions
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
