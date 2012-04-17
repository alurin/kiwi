#ifndef KIWI_LANG_EXPRESSIONNODE_INTERNAL
#define KIWI_LANG_EXPRESSIONNODE_INTERNAL

#include "Node.hpp"

namespace kiwi {
namespace lang {
    class VariableNode;
    class ArgumentNode;

    class ExpressionNode : public Node  { };

    class LeftNode : ExpressionNode    { };
    class RightNode : ExpressionNode   { };

    class BinaryNode : public RightNode {
    public:
        enum OpCode {
            ADD = 1,
            SUB,
            MUL,
            DIV,
            LSH,
            RSH,
            OR,
            AND,
            EQ,
            NEQ,
            GE,
            LE,
            GT,
            LT
        };

        BinaryNode(OpCode opcode, RightNode* left, RightNode* right, bool logic = false);

        virtual ~BinaryNode();
    protected:
        OpCode      m_opcode;
        RightNode*  m_left;
        RightNode*  m_right;
        bool        m_logic;
    };

    class UnaryNode : public RightNode {
    public:
        enum OpCode {
            NEG = 1,
            ADD,
            NOT,
            DEC,
            INC
        };

        UnaryNode(OpCode opcode, RightNode* value, bool post = false);

        virtual ~UnaryNode();
    protected:
        OpCode      m_opcode;
        RightNode*  m_value;
        bool        m_post;
    };

    class AssignNode : public RightNode {
    public:
        AssignNode(LeftNode* left, RightNode* right);

        virtual ~AssignNode();
    protected:
        LeftNode*   m_left;
        RightNode*  m_right;
    };

    class ArgumentLeftNode : public LeftNode {
    public:
        ArgumentLeftNode(ArgumentNode* arg);

    protected:
        ArgumentNode* o_arg;
    };
    class ArgumentRightNode : public RightNode {
    public:
        ArgumentRightNode(ArgumentNode* arg);

    protected:
        ArgumentNode* o_arg;
    };

    class VariableLeftNode : public LeftNode {
    public:
        VariableLeftNode(VariableNode* var);

    protected:
        VariableNode* o_var;
    };
    class VariableRightNode : public RightNode {
    public:
        VariableRightNode(VariableNode* var);

    protected:
        VariableNode* o_var;
    };

    class IntegerConstNode : public RightNode
    {
    public:
        IntegerConstNode(int32_t value);

    protected:
        int32_t m_value;
    };

    class ExpressionFactory {
    public:
        RightNode* getNeg(RightNode* value)
        {
            return new UnaryNode(UnaryNode::NEG, value);
        }

        RightNode* getAdd(RightNode* value)
        {
            return new UnaryNode(UnaryNode::ADD, value);
        }

        RightNode* getNot(RightNode* value)
        {
            return new UnaryNode(UnaryNode::NOT, value);
        }

        RightNode* getDec(RightNode* value, bool post = false)
        {
            return new UnaryNode(UnaryNode::DEC, value, post);
        }

        RightNode* getInc(RightNode* value, bool post = false)
        {
            return new UnaryNode(UnaryNode::INC, value, post);
        }

        RightNode* getAdd(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::ADD, left, right);
        }

        RightNode* getSub(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::SUB, left, right);
        }

        RightNode* getMul(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::MUL, left, right);
        }

        RightNode* getDiv(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::DIV, left, right);
        }

        RightNode* getLsh(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::LSH, left, right);
        }

        RightNode* getRsh(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::RSH, left, right);
        }

        RightNode* getOr(RightNode* left, RightNode* right, bool logic = false)
        {
            return new BinaryNode(BinaryNode::OR, left, right, logic);
        }

        RightNode* getAnd(RightNode* left, RightNode* right, bool logic = false)
        {
            return new BinaryNode(BinaryNode::AND, left, right, logic);
        }

        RightNode* getEq(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::EQ, left, right);
        }

        RightNode* getNeq(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::NEQ, left, right);
        }

        RightNode* getGe(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::GE, left, right);
        }

        RightNode* getLe(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::LE, left, right);
        }

        RightNode* getGt(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::GT, left, right);
        }

        RightNode* getLt(RightNode* left, RightNode* right)
        {
            return new BinaryNode(BinaryNode::LT, left, right);
        }

        RightNode* getAssign(LeftNode* left, RightNode* right)
        {
            return new AssignNode(left, right);
        }

        RightNode* getInt(int32_t value)
        {
            return new IntegerConstNode(value);
        }
    };
}}

#endif