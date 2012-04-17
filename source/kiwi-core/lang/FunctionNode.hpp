#ifndef KIWI_LANG_FUNCTIONNODE_INTERNAL
#define KIWI_LANG_FUNCTIONNODE_INTERNAL

#include "kiwi/codegen/Statement.hpp"
#include "kiwi/codegen/Variable.hpp"
#include "Node.hpp"
#include "boost/shared_ptr.hpp"
#include <map>
#include <vector>

namespace llvm {
    class Function;
}

namespace kiwi
{
    typedef boost::shared_ptr<class Module> ModuleRef;

namespace lang
{
    class TypeNode;
    class FunctionNode;
    class LeftNode;
    class RightNode;
    class ScopeNode;

    using codegen::StatementGen;
    using codegen::VariableGen;

    /// Statement syntax node
    class StatementNode : public Node
    {
    public:
        /// Emit instructions for statement
        virtual StatementGen emit(ModuleRef module, const StatementGen& gen) =0;

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

    /// Named parameter syntax node
    class NamedNode : public Node
    {
    public:
        /// returns type node for this named node
        TypeNode* getType() const {
            return m_type;
        }

        /// create left node for this named node
        virtual LeftNode*  getLeft() =0;

        /// create right node for this named node
        virtual RightNode* getRight() =0;

        VariableGen getGenerator() const {
            return m_gen;
        }

        void setGenerator(VariableGen gen) {
            m_gen = gen;
        }
    protected:
        FunctionNode*   o_owner;
        TypeNode*       m_type;
        VariableGen     m_gen;

        NamedNode(FunctionNode* owner, TypeNode* type);
    };

    /// Argument syntax node
    class ArgumentNode : public NamedNode
    {
    public:
        ArgumentNode(FunctionNode* owner, const Identifier& name, TypeNode* type);

        virtual ~ArgumentNode();

        Identifier getName() const {
            return m_name;
        }

        /// create left node for this named node
        virtual LeftNode* getLeft();

        /// create right node for this named node
        virtual RightNode* getRight();
    protected:
        Identifier    m_name;
    };

    /// Variable syntax node
    class VariableNode : public NamedNode
    {
    public:
        VariableNode(ScopeNode* owner, const Identifier& name, TypeNode* type);

        virtual ~VariableNode();

        Identifier getName() const {
            return m_name;
        }

        /// create left node for this named node
        virtual LeftNode* getLeft();

        /// create right node for this named node
        virtual RightNode* getRight();
    protected:
        ScopeNode*    o_owner;
        Identifier    m_name;
    };

    /// Expression statment node
    class ExpressionNode : public StatementNode
    {
    public:
        ExpressionNode(ScopeNode* parent, RightNode* expr);

        ~ExpressionNode();

        /// Emit instructions for expression
        virtual StatementGen emit(ModuleRef module, const StatementGen& gen);
    protected:
        RightNode* m_expr;
    };

    /// Scope syntax node for collect variables and statements
    class ScopeNode : public StatementNode {
    public:
        ScopeNode(FunctionNode* parent);
        ScopeNode(ScopeNode* parent);
        virtual ~ScopeNode();

        /// declare scope variable
        VariableNode* declare(const Identifier& name, TypeNode* type);

        /// returns named node from scope
        NamedNode* get(const Identifier& name);

        /// add statement node
        void append(StatementNode* scope);

        /// add expression node
        void append(RightNode* expr);

        /// Emit instructions for scope statement
        virtual StatementGen emit(ModuleRef module, const StatementGen& gen);
    protected:
        std::map<Identifier, VariableNode*> m_vars;
        std::vector<StatementNode*>         m_stmts;
    };

    class FunctionNode : public Node
    {
    public:
        /// construct function node
        FunctionNode(const Identifier& name, TypeNode* type);

        /// destructor
        virtual ~FunctionNode();

        /// declare function argument
        ArgumentNode* declare(const Identifier& name, TypeNode* type);

        /// get function arguments
        ArgumentNode* get(const Identifier& name);

        /// Returns root scope
        ScopeNode* getRoot() const {
            return m_root;
        }

        void generate(ModuleRef module);

        llvm::Function* getFunction() {
            return m_func;
        }
    protected:
        Identifier      m_name;
        TypeNode*       m_type;
        ScopeNode*      m_root;

        llvm::Function* m_func;

        std::map<Identifier, ArgumentNode*> m_args;
    };

}}

#endif