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
#include <vector>
#include <list>

namespace kiwi {
    class Context;
    class ObjectType;
    class Callable;

    class ValueBuilder;
    class BlockBuilder;
    class VariableBuilder;

namespace lang {
    class NamedNode;
    class Driver;
    class TypeNode;
    class CompoundNode;
    class ThisNode;

    //==--------------------------------------------------------------------==//
    /// Mutable synatax node
    class MutableNode : public Node {
    public:
        /// Emit instructions for store value
        ValueBuilder emit(Driver& driver, ValueBuilder value) const;

    protected:
        virtual ValueBuilder emitImpl(Driver& driver, ValueBuilder value) const =0;
    };

    //==--------------------------------------------------------------------==//
    /// Expression syntax node
    class ExpressionNode : public Node {
    public:
        /// Emit instruction for receive value
        ValueBuilder emit(Driver& driver, BlockBuilder block) const;

    protected:
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const =0;
    };

    //==--------------------------------------------------------------------==//
    /// Arument for callable syntax node
    class CallableArgument : public Node {
        friend class CallableNode;
    public:
        virtual ~CallableArgument();

        /// proxy for value
        ValueBuilder emit(Driver& driver, BlockBuilder block) const;
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
        //void prepend(ExpressionNode* value);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;

    protected:
        /// list of arguments
        ArgumentList m_arguments;

        /// constructor
        CallableNode();

        /// Find arguments for append before other
        virtual ValueBuilder emitCall(Driver& driver, BlockBuilder block, std::vector<ValueBuilder> args) const;

        /// Find callable for current node
        virtual CallablePtr findCallable(Driver& driver, std::vector<TypePtr> types) const =0;
    };

    //==--------------------------------------------------------------------==//
    /// Binary expression syntax node
    class BinaryNode : public CallableNode {
    public:
        /// Constructor
        BinaryNode(Member::BinaryOpcode opcode, ExpressionNode* left, ExpressionNode* right, bool logic = false);

        /// Find callable for current node
        virtual CallablePtr findCallable(Driver& driver, std::vector<TypePtr> types) const;
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
        virtual CallablePtr findCallable(Driver& driver, std::vector<TypePtr> types) const;
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
        virtual CallablePtr findCallable(Driver& driver, std::vector<TypePtr> types) const;
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
        virtual CallablePtr findCallable(Driver& driver, std::vector<TypePtr> types) const;
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
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
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
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
    protected:
        /// Left expression node
        MutableNode* m_left;

        /// Right expression node
        ExpressionNode* m_right;
    };

    //==--------------------------------------------------------------------==//
    /// Named mutable syntax node
    class NamedMutableNode : public MutableNode {
    public:
        /// Constructor
        NamedMutableNode(NamedNode* var);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, ValueBuilder value) const;
    protected:
        /// Named node
        NamedNode* o_var;
    };

    //==--------------------------------------------------------------------==//
    /// Named expression syntax node
    class NamedExpressionNode : public ExpressionNode {
    public:
        /// Constructor
        NamedExpressionNode(NamedNode* var);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
    protected:
        /// Named node
        NamedNode* o_var;
    };

    /// TODO: ADD COMMETS ====================================================//
    //==--------------------------------------------------------------------==//
    class InstanceMutableNode : public MutableNode {
    public:
        InstanceMutableNode(ThisNode* thisNode, const Identifier& name);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, ValueBuilder value) const;
    protected:
        ThisNode*  m_thisNode;
        Identifier m_name;
    };

    //==--------------------------------------------------------------------==//
    class InstanceExpressionNode : public ExpressionNode {
    public:
        InstanceExpressionNode(ThisNode* thisNode, const Identifier& name);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
    protected:
        ThisNode*  m_thisNode;
        Identifier m_name;
    };

    //==--------------------------------------------------------------------==//
    class IntegerConstNode : public ExpressionNode
    {
    public:
        IntegerConstNode(ContextPtr context, int32_t value);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
    protected:
        ContextPtr  m_context;
        int32_t     m_value;
    };

    //==--------------------------------------------------------------------==//
    class StringConstNode : public ExpressionNode
    {
    public:
        StringConstNode(ContextPtr context, const String& value);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
    protected:
        ContextPtr  m_context;
        String      m_value;
    };

    //==--------------------------------------------------------------------==//
    class CharConstNode : public ExpressionNode
    {
    public:
        CharConstNode(ContextPtr context, const UChar& value);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
    protected:
        ContextPtr  m_context;
        UChar     m_value;
    };

    //==--------------------------------------------------------------------==//
    class BoolConstNode : public ExpressionNode
    {
    public:
        BoolConstNode(ContextPtr context, bool value);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
    protected:
        ContextPtr  m_context;
        bool        m_value;
    };

    //==--------------------------------------------------------------------==//
    class ThisNode : public ExpressionNode {
    public:
        ThisNode(CompoundNode* thisType);

        /// Emit instructions
        virtual ValueBuilder emitImpl(Driver& driver, BlockBuilder block) const;
    protected:
        CompoundNode* m_thisType;
    };

}}

#endif
