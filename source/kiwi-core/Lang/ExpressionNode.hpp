/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_LANG_EXPRESSIONNODE_INTERNAL
#define KIWI_LANG_EXPRESSIONNODE_INTERNAL

#include "Node.hpp"
#include "kiwi/Member.hpp"
#include "kiwi/Codegen/Expression.hpp"
#include "kiwi/Codegen/Variable.hpp"
#include <vector>
#include <list>

namespace kiwi {
    class Context;
    class ObjectType;
    class Callable;

namespace lang {
    class VariableNode;
    class ArgumentNode;
    class Driver;
    class TypeNode;

    using codegen::ExpressionGen;
    using codegen::StatementGen;
    using codegen::VariableGen;

    //==--------------------------------------------------------------------==//
    /// Mutable synatax node
    class MutableNode : public Node {
    public:
        /// Emit instructions for store value
        virtual ExpressionGen emit(Driver& driver, const ExpressionGen& gen) =0;
    };

    //==--------------------------------------------------------------------==//
    /// Expression syntax node
    class ExpressionNode : public Node {
    public:
        /// Emit instruction for receive value
        virtual ExpressionGen emit(Driver& driver, const StatementGen& value) =0;
    };

    //==--------------------------------------------------------------------==//
    /// Arument for callable syntax node
    class CallableArgument {
        friend class CallableNode;
    public:
        virtual ~CallableArgument();

        /// proxy for value
        ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        /// argument name
        Identifier m_name;

        /// argument value
        ExpressionNode* m_value;

        /// argument position
        int32_t m_position;

        /// named constructor
        CallableArgument(const Identifier& name, ExpressionNode* value, int32_t position);

        /// position constructor
        CallableArgument(ExpressionNode* value, int32_t position);
    };

    //==--------------------------------------------------------------------==//
    /// Callable syntax node. Base for all callable expression: binary, unary,
    /// multinary, methods calls, new, invoke object and e.t.c
    class CallableNode : public ExpressionNode {
    public:
        typedef std::list<CallableArgument*> ArgumentList;

        /// destructor
        virtual ~CallableNode();

        /// Append positioned argument
        void append(ExpressionNode* value);

        /// Append names argument
        void append(const Identifier& name, ExpressionNode* value);

        /// Add positioned argument
        void prepend(ExpressionNode* value);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);

    protected:
        /// list of arguments
        ArgumentList m_arguments;

        /// constructor
        CallableNode();

        /// Find arguments for append before other
        virtual ExpressionGen emitCall(Driver& driver, const StatementGen& gen, std::vector<ExpressionGen> args);

        /// Find callable for current node
        virtual Callable* findCallable(Driver& driver, std::vector<Type*> types) =0;
    };

    //==--------------------------------------------------------------------==//
    /// Binary expression syntax node
    class BinaryNode : public CallableNode {
    public:
        /// Constructor
        BinaryNode(Member::BinaryOpcode opcode, ExpressionNode* left, ExpressionNode* right, bool logic = false);

        /// Find callable for current node
        virtual Callable* findCallable(Driver& driver, std::vector<Type*> types);
    protected:
        /// Binary operation opcode
        Member::BinaryOpcode m_opcode;

        // Binary operator (`and` or `or`) is logic?
        bool m_logic;
    };

    //==--------------------------------------------------------------------==//
    /// Unary expression syntax node
    class UnaryNode : public CallableNode {
    public:
        /// Constructor
        UnaryNode(Member::UnaryOpcode opcode, ExpressionNode* value, bool post = false);


        /// Find callable for current node
        virtual Callable* findCallable(Driver& driver, std::vector<Type*> types);
    protected:
        /// Unary operation opcode
        Member::UnaryOpcode m_opcode;

        /// Post expression
        /// @todo Remove. ++ -- is operators for mutable expressions
        bool m_post;
    };

    //==--------------------------------------------------------------------==//
    /// Multiary expression syntax node
    class MultiaryNode : public CallableNode {
    public:
        /// constructor
        MultiaryNode(Member::MultiaryOpcode opcode, ExpressionNode* value);

        /// Find callable for current node
        virtual Callable* findCallable(Driver& driver, std::vector<Type*> types);
    protected:
        Member::MultiaryOpcode m_opcode;

        /// constructor for new
        MultiaryNode(Member::MultiaryOpcode opcode);
    };

    //==--------------------------------------------------------------------==//
    /// Call expression syntax node.
    /// @todo Slice to two classes
    class CallNode : public CallableNode {
    public:
        CallNode(ExpressionNode* expr, const Identifier& method);

        /// Find callable for current node
        virtual Callable* findCallable(Driver& driver, std::vector<Type*> types);
    protected:
        Identifier                  m_method;
    };

    //==--------------------------------------------------------------------==//
    // New operator syntax node
    class NewNode : public MultiaryNode {
    public:
        /// constructor
        NewNode(TypeNode* type);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        TypeNode* m_type;
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
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
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
        virtual ExpressionGen emit(Driver& driver, const ExpressionGen& gen);
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
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
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
        virtual ExpressionGen emit(Driver& driver, const ExpressionGen& gen);
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
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        /// Varaible node
        VariableNode* o_var;
    };

    /// TODO: ADD COMMETS ====================================================//
    //==--------------------------------------------------------------------==//
    class InstanceMutableNode : public MutableNode {
    public:
        InstanceMutableNode(const Identifier& name);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const ExpressionGen& gen);
    protected:
        Identifier m_name;
    };

    //==--------------------------------------------------------------------==//
    class InstanceExpressionNode : public ExpressionNode {
    public:
        InstanceExpressionNode(const Identifier& name);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        Identifier m_name;
    };

    //==--------------------------------------------------------------------==//
    class IntegerConstNode : public ExpressionNode
    {
    public:
        IntegerConstNode(Context* context, int32_t value);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        Context*  m_context;
        int32_t     m_value;
    };

    //==--------------------------------------------------------------------==//
    class StringConstNode : public ExpressionNode
    {
    public:
        StringConstNode(Context* context, const String& value);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        Context*  m_context;
        String      m_value;
    };

    //==--------------------------------------------------------------------==//
    class CharConstNode : public ExpressionNode
    {
    public:
        CharConstNode(Context* context, const UChar& value);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        Context*  m_context;
        UChar     m_value;
    };

    //==--------------------------------------------------------------------==//
    class BoolConstNode : public ExpressionNode
    {
    public:
        BoolConstNode(Context* context, bool value);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        Context*  m_context;
        bool        m_value;
    };

    //==--------------------------------------------------------------------==//
    class ThisNode : public ExpressionNode {
    public:
        ThisNode(ObjectType* thisType);

        /// Emit instructions
        virtual ExpressionGen emit(Driver& driver, const StatementGen& gen);
    protected:
        ObjectType* m_thisType;
    };
}}

#endif
