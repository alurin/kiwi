#ifndef KIWI_LANG_STATEMENTNODE_INTERNAL
#define KIWI_LANG_STATEMENTNODE_INTERNAL

#include "Node.hpp"
#include "kiwi/codegen/Statement.hpp"

namespace kiwi
{
namespace lang
{
    class TypeNode;
    class FunctionNode;
    class ScopeNode;
    class RightNode;

    using codegen::StatementGen;

    /// Statement syntax node
    class StatementNode : public Node {
    public:
        /// emit instructions for statement
        virtual StatementGen emit(const StatementGen& gen) =0;

        /// returns parent function node
        FunctionNode* getOwner() const {
            return o_owner;
        }

        /// returns parent scope
        ScopeNode* getParent() const {
            return o_parent;
        }
    protected:
        FunctionNode*   o_owner;
        ScopeNode*      o_parent;

        /// Create root statement
        StatementNode(FunctionNode* parent);

        /// Create paret
        StatementNode(ScopeNode* parent);
    };

    /// Return statement syntax node
    class ReturnStatement : public StatementNode {
    public:
        /// constructor
        ReturnStatement(ScopeNode* parent);

        /// constructor
        ReturnStatement(ScopeNode* parent, RightNode* result);

        /// destructor
        ~ReturnStatement();

        /// emit instructions for statement
        virtual StatementGen emit(const StatementGen& gen);
    protected:
        RightNode* m_result;
    };

    /// Print statement syntax node
    class PrintStatement : public StatementNode {
    public:
        /// constructor
        PrintStatement(ScopeNode* parent, RightNode* result);

        /// destructor
        ~PrintStatement();

        /// emit instructions for statement
        virtual StatementGen emit(const StatementGen& gen);
    protected:
        RightNode* m_result;
    };
}}

#endif