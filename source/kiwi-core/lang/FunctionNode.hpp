#ifndef KIWI_LANG_FUNCTIONNODE_INTERNAL
#define KIWI_LANG_FUNCTIONNODE_INTERNAL

#include "kiwi/codegen/Variable.hpp"
#include "StatementNode.hpp"
#include "boost/shared_ptr.hpp"
#include <map>
#include <vector>

namespace llvm {
    class Function;
}

namespace kiwi
{
    typedef boost::shared_ptr<class Module> ModuleRef;
    typedef boost::shared_ptr<class Method> MethodRef;

namespace lang
{
    class TypeNode;
    class FunctionNode;
    class MutableNode;
    class ExpressionNode;
    class ScopeNode;

    using codegen::VariableGen;

    /// Named parameter syntax node
    class NamedNode : public Node
    {
    public:
        // destructor
        virtual ~NamedNode();

        /// returns type node for this named node
        TypeNode* getType() const {
            return m_type;
        }

        /// create left node for this named node
        virtual MutableNode*  getLeft() =0;

        /// create right node for this named node
        virtual ExpressionNode* getRight() =0;

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
        virtual MutableNode* getLeft();

        /// create right node for this named node
        virtual ExpressionNode* getRight();
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
        virtual MutableNode* getLeft();

        /// create right node for this named node
        virtual ExpressionNode* getRight();
    protected:
        ScopeNode*    o_owner;
        Identifier    m_name;
    };

    /// Expression statment node
    class ExpressionStatementNode : public StatementNode
    {
    public:
        ExpressionStatementNode(ScopeNode* parent, ExpressionNode* expr);

        virtual ~ExpressionStatementNode();

        /// Emit instructions for expression
        virtual StatementGen emit(const StatementGen& gen);
    protected:
        ExpressionNode* m_expr;
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
        void append(ExpressionNode* expr);

        /// Emit instructions for scope statement
        virtual StatementGen emit(const StatementGen& gen);
    protected:
        std::map<Identifier, VariableNode*> m_vars;
        std::vector<StatementNode*>         m_stmts;
    };

    /// Field syntax node
    class FieldNode : public Node {
    public:
        FieldNode(const Identifier& name, TypeNode* type);

        virtual ~FieldNode();

        /// Generate metadata
        virtual void generate(TypeRef owner);
    protected:
        // store fields
        Identifier                  m_name;
        TypeNode*                   m_type;
    };

    /// Function syntx node
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

        /// Generate metadata
        virtual void generate(TypeRef owner);

        /// Emit function code and instruction
        void emit(TypeRef owner);

        llvm::Function* getFunction() {
            return m_func;
        }
    protected:
        // store fields
        Identifier                  m_name;
        TypeNode*                   m_type;
        ScopeNode*                  m_root;

        // generated fields
        MethodRef                   m_method;
        llvm::Function*             m_func;
        std::vector<ArgumentNode*>  m_positions;

        std::map<Identifier, ArgumentNode*> m_args;
    };

}}

#endif