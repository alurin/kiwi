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
        IdentRuler() { }
        IdentRuler(const IdentRuler& identRuler) : m_idents(identRuler.m_idents) { }

        void add(UChar rule) {
            m_idents.push_back(rule);
        }

        void write(OutputStream* stream) const {
            for (size_t i = 0; i < m_idents.size(); ++i) {
                stream->write(m_idents[i]);
            }
        }

        IdentRuler begin() {
            IdentRuler ruler = *this;
            ruler.add(' ');
            return ruler;
        }

        IdentRuler center() {
            IdentRuler ruler = *this;
            ruler.add(BOX_LINE);
            return ruler;
        }

        IdentRuler end() {
            IdentRuler ruler = *this;
            ruler.add(' ');
            return ruler;
        }
    protected:
        ///
        std::vector<UChar> m_idents;
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
    m_stream->write("use ");
    m_stream->write('$');
    m_stream->writeln(node->getName());
}

/// Print unary expression  node
void ExpressionPrinter::visit(UnaryExpressionNode* node) {
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

    // root node
    m_stream->writeln(BOX_ENTER);

    // first node
    m_ruler.write(m_stream);
    m_stream->write(BOX_CENTER);
    m_stream->write(BOX_LEAF);
    m_stream->write(' ');
    m_stream->writeln(chr);

    // second node
    m_ruler.write(m_stream);
    m_stream->write(BOX_END);
    IdentRuler ruler = m_ruler.end();
    ExpressionPrinter printer(m_stream, ruler);
    node->getNode()->accept(printer);
}

/// Print binary expression  node
void ExpressionPrinter::visit(BinaryExpressionNode* node) {
    // first node
    m_stream->write(BOX_BEGIN);
    m_stream->write(BOX_LEAF);
    m_stream->write(' ');

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
    m_stream->writeln(chr);

    // second node
    m_ruler.write(m_stream);
    m_stream->write(BOX_CENTER);
    {
        IdentRuler ruler(m_ruler);
        ruler.add(BOX_LINE);
        ruler.add(' ');
        ExpressionPrinter printer(m_stream, ruler);
        node->getLeftNode()->accept(printer);
    }

    // third node
    m_ruler.write(m_stream);
    m_stream->write(BOX_END);
    {
        IdentRuler ruler(m_ruler);
        ruler.add(' ');
        ruler.add(' ');
        ExpressionPrinter printer(m_stream, m_ruler);
        node->getRightNode()->accept(printer);
    }
}

/// Print assignment expression  node
void ExpressionPrinter::visit(AssignmentExpressionNode* node) {
    // root node
    m_stream->writeln(BOX_ENTER);

    // first node
    m_ruler.write(m_stream);
    m_stream->write(BOX_CENTER);
    m_stream->write(BOX_LEAF);
    m_stream->write(' ');
    m_stream->writeln('=');

    // second node
    m_ruler.write(m_stream);
    m_stream->write(BOX_CENTER);
    {
        LeftExpressionPrinter printer(m_stream, m_ruler.center());
        node->getLeftNode()->accept(printer);
    }

    // third node
    m_ruler.write(m_stream);
    m_stream->write(BOX_END);
    {
        ExpressionPrinter printer(m_stream, m_ruler.end());
        node->getRightNode()->accept(printer);
    }
}

/// Print integer node
void ExpressionPrinter::visit(IntegerNode* node) {
    // node->getValue();

}

/// Print boolean node
void ExpressionPrinter::visit(BooleanNode* node) {

}

/// Print string node
void ExpressionPrinter::visit(StringNode* node) {

}

/// Print char node
void ExpressionPrinter::visit(CharNode* node) {

}

/// Print nullable node
void ExpressionPrinter::visit(NullableNode* node) {

}

/// Print variable node
void ExpressionPrinter::visit(RightVariableNode* node) {
    m_stream->write(BOX_LEAF);
    m_stream->write(' ');
    m_stream->write('$');
    m_stream->writeln(node->getVariable()->getName());
}

/// Print variable node
void LeftExpressionPrinter::visit(LeftVariableNode* node) {
    m_stream->write(BOX_LEAF);
    m_stream->write(' ');
    m_stream->write('$');
    m_stream->writeln(node->getVariable()->getName());
}

/// Print expression statement node
void StatementPrinter::visit(ExpressionStatementNode* node) {
    ExpressionPrinter printer(m_stream, m_ruler);
    node->getChildNode()->accept(printer);
}

/// Print scope statement node
void StatementPrinter::visit(ScopeStatementNode* node) {
    // first node
    m_stream->writeln(BOX_ENTER);

    // dump variables in scope
    {
        NodePrinter printer(m_stream, m_ruler);
        ScopeStatementNode::VariableIterator
            var = node->var_begin(),
            ve  = node->var_end();
        for (; var != ve; ++var) {
            // (var->second)->accept(printer);
        }
    }

    // dump statements
    {
        ScopeStatementNode::StatementIterator
            stmt = node->stmt_begin(),
            se   = node->stmt_end();
        size_t count = node->stmt_size();

        IdentRuler center = m_ruler, normal = m_ruler, ruler = m_ruler;
        normal.add(' ');
        if (count > 1) {
            center.add(BOX_LINE);
        } else {
            center.add(' ');
        }

        for (size_t i = 0; stmt != se; ++stmt, ++i) {
            // write ruler if not first
            m_ruler.write(m_stream);
            if (i == 0) {
                if (count > 1) {
                    m_stream->write(BOX_CENTER);
                    ruler = center;
                } else {
                    m_stream->write(BOX_END);
                    ruler = normal;
                }
            } else {
                if (i + 1 != count) {
                    m_stream->write(BOX_CENTER);
                    ruler = center;
                } else {
                    m_stream->write(BOX_END);
                    ruler = normal;
                }
            }

            StatementPrinter printer(m_stream, ruler);
            (*stmt)->accept(printer);
        }
    }
}

/// Print conditional statement node
void StatementPrinter::visit(ConditionalStatementNode* node) {

}

/// Print condition loop node
void StatementPrinter::visit(ConditionLoopNode* node) {

}