#include "kiwi/IO/Stream.hpp"
#include "kiwi/Script/NodeVisitor.hpp"
#include "kiwi/Script/StatementNode.hpp"
#include "kiwi/Script/ExpressionNode.hpp"
#include <vector>

using namespace kiwi;
using namespace kiwi::io;
using namespace kiwi::script;

namespace {
    const UChar BOX_START  = L'\x2500'; // ─
    const UChar BOX_LEAF   = L'\x2500'; // ╌
    const UChar BOX_ENTER  = L'\x2510'; // ┐
    const UChar BOX_BEGIN  = L'\x252C'; // ┬
    const UChar BOX_LINE   = L'\x2502'; // │
    const UChar BOX_CENTER = L'\x251C'; // ├
    const UChar BOX_END    = L'\x2514'; // └

    class IdentRuler {
    public:
        IdentRuler() : m_count(1), m_index(0) { }
        IdentRuler(const IdentRuler& identRuler) : m_idents(identRuler.m_idents), m_count(1), m_index(0)  { }

        void add(UChar rule) {
            m_idents.push_back(rule);
        }

        void write(OutputStream* stream) {
            m_index++;

            if (m_index != 1) {
                for (size_t i = 0; i < m_idents.size(); ++i) {
                    stream->write(m_idents[i]);
                }
            }

            if (m_count == 1) {
                stream->write(BOX_START);
            } else if (m_index == 1) {
                stream->write(BOX_BEGIN);
            } else if (m_count == m_index) {
                stream->write(BOX_END);
            } else {
                stream->write(BOX_CENTER);
            }
        }

        IdentRuler get() {
            IdentRuler ruler = *this;
            if (m_index == m_count) {
                ruler.add(' ');
            } else {
                ruler.add(BOX_LINE);
            }
            return ruler;
        }

        void setCount(size_t count) {
            m_count = count;
        }

        size_t getCount() const {
            return m_count;
        }
    protected:
        /// List of ident characters
        std::vector<UChar> m_idents;

        /// Count
        size_t m_count;

        /// Index
        size_t m_index;
    };

    class NodePrinter : public NodeVisitor {
    public:
        NodePrinter(OutputStream* stream, const IdentRuler& identRuler);

        /// Visit expression expression node
        virtual void visit(ExpressionNode* node);

        /// Visit expression expression node
        virtual void visit(LeftExpressionNode* node);

        /// Visit statement node
        virtual void visit(StatementNode* node);

        /// Visit variable node
        virtual void visit(VariableNode* node);
    protected:
        /// Output stream
        OutputStream* m_stream;

        /// Ident level
        IdentRuler m_ruler;
    };

    class ExpressionPrinter : public ExpressionVisitor {
    public:
        ExpressionPrinter(OutputStream* stream, const IdentRuler& identRuler);

        /// Visit unary expression node
        virtual void visit(UnaryExpressionNode* node);

        /// Visit binary expression node
        virtual void visit(BinaryExpressionNode* node);

        /// Visit assignment expression node
        virtual void visit(AssignmentExpressionNode* node);

        /// Visit integer node
        virtual void visit(IntegerNode* node);

        /// Visit boolean node
        virtual void visit(BooleanNode* node);

        /// Visit string node
        virtual void visit(StringNode* node);

        /// Visit char node
        virtual void visit(CharNode* node);

        /// Visit nullable node
        virtual void visit(NullableNode* node);

        /// Visit variable node
        virtual void visit(RightVariableNode* node);
    protected:
        /// Output stream
        OutputStream* m_stream;

        /// Ident level
        IdentRuler m_ruler;
    };

    class LeftExpressionPrinter : public LeftExpressionVisitor {
    public:
        LeftExpressionPrinter(OutputStream* stream, const IdentRuler& identRuler);

        /// Visit variable node
        virtual void visit(LeftVariableNode* node);
    protected:
        /// Output stream
        OutputStream* m_stream;

        /// Ident level
        IdentRuler m_ruler;
    };

    class StatementPrinter : public StatementVisitor {
    public:
        StatementPrinter(OutputStream* stream, const IdentRuler& identRuler);

        /// Visit expression statement node
        virtual void visit(ExpressionStatementNode* node);

        /// Visit scope statement node
        virtual void visit(ScopeStatementNode* node);

        /// Visit conditional statement node
        virtual void visit(ConditionalStatementNode* node);

        /// Visit condition loop node
        virtual void visit(ConditionLoopNode* node);
    protected:
        /// Output stream
        OutputStream* m_stream;

        /// Ident level
        IdentRuler m_ruler;
    };
} // anonym namespace

// Dump AST
void Node::dump(Node* node, io::OutputStream* stream) {
    // root
    stream->write(BOX_START);

    // node
    IdentRuler ruler;
    ruler.add(' ');
    NodePrinter printer(stream, ruler);
    node->accept(printer);
}

// NodePrinter constructor
NodePrinter::NodePrinter(OutputStream* stream, const IdentRuler& identRuler)
: m_stream(stream), m_ruler(identRuler) {

}

// ExpressionPrinter constructor
ExpressionPrinter::ExpressionPrinter(OutputStream* stream, const IdentRuler& identRuler)
: m_stream(stream), m_ruler(identRuler) {

}

// LeftExpressionPrinter constructor
LeftExpressionPrinter::LeftExpressionPrinter(OutputStream* stream, const IdentRuler& identRuler)
: m_stream(stream), m_ruler(identRuler) {

}

// StatementPrinter constructor
StatementPrinter::StatementPrinter(OutputStream* stream, const IdentRuler& identRuler)
: m_stream(stream), m_ruler(identRuler) {

}

/// Print expression  node
void NodePrinter::visit(ExpressionNode* node) {
    ExpressionPrinter printer(m_stream, m_ruler);
    node->accept(printer);
}

/// Print left expression  node
void NodePrinter::visit(LeftExpressionNode* node) {
    LeftExpressionPrinter printer(m_stream, m_ruler);
    node->accept(printer);
}

/// Print statement node
void NodePrinter::visit(StatementNode* node) {
    StatementPrinter printer(m_stream, m_ruler);
    node->accept(printer);
}

/// Print statement node
void NodePrinter::visit(VariableNode* node) {
    m_stream->write(BOX_LEAF);
    m_stream->write(" use $");
    m_stream->writeln(node->getName());
}

/// Print unary expression  node
void ExpressionPrinter::visit(UnaryExpressionNode* node) {
    m_ruler.setCount(2);
    UChar chr;
    switch (node->getOpcode()) {
        case UnaryExpressionNode::OP_NOT:
            chr = '!';
            break;
        case UnaryExpressionNode::OP_POS:
            chr = '+';
            break;
        case UnaryExpressionNode::OP_NEG:
            chr = '-';
            break;
    }

    // first node
    m_ruler.write(m_stream);
    m_stream->write(BOX_LEAF);
    m_stream->write(' ');
    m_stream->writeln(chr);

    // second node
    m_ruler.write(m_stream);
    ExpressionPrinter printer(m_stream, m_ruler.get());
    node->getNode()->accept(printer);
}

/// Print binary expression  node
void ExpressionPrinter::visit(BinaryExpressionNode* node) {
    m_ruler.setCount(3);

    UChar chr;
    switch (node->getOpcode()) {
        case BinaryExpressionNode::OP_ADD:
            chr = '+';
            break;
        case BinaryExpressionNode::OP_SUB:
            chr = '-';
            break;
        case BinaryExpressionNode::OP_MUL:
            chr = '*';
            break;
        case BinaryExpressionNode::OP_DIV:
            chr = '/';
            break;
    }

    // first node
    m_ruler.write(m_stream);
    m_stream->write(BOX_LEAF);
    m_stream->write(' ');
    m_stream->writeln(chr);

    // second node
    {
        m_ruler.write(m_stream);
        ExpressionPrinter printer(m_stream, m_ruler.get());
        node->getLeftNode()->accept(printer);
    }

    // third node
    {
        m_ruler.write(m_stream);
        ExpressionPrinter printer(m_stream, m_ruler.get());
        node->getRightNode()->accept(printer);
    }
}

/// Print assignment expression  node
void ExpressionPrinter::visit(AssignmentExpressionNode* node) {
    m_ruler.setCount(3);

    // first node
    //m_ruler.write(m_stream);
    //m_stream->write(BOX_CENTER);
    m_ruler.write(m_stream);
    m_stream->writeln(" =");

    // second node
    {
        m_ruler.write(m_stream);
        LeftExpressionPrinter printer(m_stream, m_ruler.get());
        node->getLeftNode()->accept(printer);
    }

    // third node
    {
        m_ruler.write(m_stream);
        ExpressionPrinter printer(m_stream, m_ruler.get());
        node->getRightNode()->accept(printer);
    }
}

/// Print integer node
void ExpressionPrinter::visit(IntegerNode* node) {
    // node->getValue();

}

/// Print boolean node
void ExpressionPrinter::visit(BooleanNode* node) {
    m_stream->write(BOX_LEAF);
    if (node->getValue())
        m_stream->writeln(" true");
    else
        m_stream->writeln(" false");
}

/// Print string node
void ExpressionPrinter::visit(StringNode* node) {
    m_stream->write(BOX_LEAF);
    m_stream->write(" ");
    m_stream->writeln(node->getValue());
}

/// Print char node
void ExpressionPrinter::visit(CharNode* node) {
    m_stream->write(BOX_LEAF);
    m_stream->write(" ");
    m_stream->writeln(node->getValue());
}

/// Print nullable node
void ExpressionPrinter::visit(NullableNode* node) {
    m_stream->write(BOX_LEAF);
    m_stream->writeln(" null");
}

/// Print variable node
void ExpressionPrinter::visit(RightVariableNode* node) {
    m_stream->write(BOX_LEAF);
    m_stream->write(" $");
    m_stream->writeln(node->getVariable()->getName());
}

/// Print variable node
void LeftExpressionPrinter::visit(LeftVariableNode* node) {
    m_stream->write(BOX_LEAF);
    m_stream->write(" $");
    m_stream->writeln(node->getVariable()->getName());
}

/// Print expression statement node
void StatementPrinter::visit(ExpressionStatementNode* node) {
    ExpressionPrinter printer(m_stream, m_ruler);
    node->getChildNode()->accept(printer);
}

/// Print scope statement node
void StatementPrinter::visit(ScopeStatementNode* node) {
    m_ruler.setCount(node->var_size() + node->stmt_size());

    // dump variables in scope
    {
        ScopeStatementNode::VariableIterator
            var = node->var_begin(),
            ve  = node->var_end();
        for (; var != ve; ++var) {
            m_ruler.write(m_stream);
            NodePrinter printer(m_stream, m_ruler.get());
            (var->second)->accept(printer);
        }
    }

    // dump statements
    {
        ScopeStatementNode::StatementIterator
            stmt = node->stmt_begin(),
            se   = node->stmt_end();

        for (size_t i = 0; stmt != se; ++stmt, ++i) {
            m_ruler.write(m_stream);
            StatementPrinter printer(m_stream, m_ruler.get());
            (*stmt)->accept(printer);
        }
    }
}

/// Print conditional statement node
void StatementPrinter::visit(ConditionalStatementNode* node) {
    // first node
    //m_stream->writeln(BOX_ENTER);
    m_ruler.setCount(node->getFalseStatement() ? 4 : 3);

    // second node: conditional
    {
        m_ruler.write(m_stream);
        m_stream->writeln(" if");
    }
    // second node: conditional
    {
        m_ruler.write(m_stream);
        ExpressionPrinter printer(m_stream, m_ruler.get());
        node->getConditional()->accept(printer);
    }

    // 3th node: true statement
    {
        m_ruler.write(m_stream);
        StatementPrinter printer(m_stream, m_ruler.get());
        node->getTrueStatement()->accept(printer);
    }

    // 4 node: false statement
    if (node->getFalseStatement()) {
        m_ruler.write(m_stream);
        StatementPrinter printer(m_stream,  m_ruler.get());
        node->getFalseStatement()->accept(printer);
    }
}

/// Print condition loop node
void StatementPrinter::visit(ConditionLoopNode* node) {
    m_ruler.setCount(3);

    // first node:
    {
        //m_ruler.write(m_stream);
        m_ruler.write(m_stream);
        if (node->getPosition() == ConditionLoopNode::PRE) {
            m_stream->writeln(" while");
        } else {
            m_stream->writeln(" repeat");
        }
    }
    // second node: conditional
    {
        m_ruler.write(m_stream);
        ExpressionPrinter printer(m_stream, m_ruler.get());
        node->getConditional()->accept(printer);
    }

    // 3th node: true statement
    {
        m_ruler.write(m_stream);
        StatementPrinter printer(m_stream, m_ruler.get());
        node->getStatement()->accept(printer);
    }
}