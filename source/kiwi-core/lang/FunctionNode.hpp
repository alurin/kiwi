#ifndef KIWI_LANG_FUNCTIONNODE_INTERNAL
#define KIWI_LANG_FUNCTIONNODE_INTERNAL

#include "kiwi/Config.hpp"
#include "Node.hpp"
#include "boost/shared_ptr.hpp"
#include <map>

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

    /// Named parameter syntax node
    class NamedNode : public Node
    {
    public:
        /// create left node for this named node
        virtual LeftNode*  getLeft() =0;

        /// create right node for this named node
        virtual RightNode* getRight() =0;
    protected:
        NamedNode();
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

        TypeNode* getType() const {
            return m_type;
        }

        /// create left node for this named node
        virtual LeftNode* getLeft();

        /// create right node for this named node
        virtual RightNode* getRight();
    protected:
        FunctionNode* o_owner;
        Identifier    m_name;
        TypeNode*     m_type;
    };

    /// Variable syntax node
    class VariableNode : public NamedNode
    {
    public:
        VariableNode(ScopeNode* owner, const Identifier& name, TypeNode* type);

        virtual ~VariableNode();

        /// create left node for this named node
        virtual LeftNode* getLeft();

        /// create right node for this named node
        virtual RightNode* getRight();
    protected:
        ScopeNode*    o_owner;
        Identifier    m_name;
        TypeNode*     m_type;
    };

    class ScopeNode : public Node {
    public:
        ScopeNode(FunctionNode* parent);
        ScopeNode(ScopeNode* parent);
        virtual ~ScopeNode();

        /// declare scope variable
        VariableNode* declare(const Identifier& name, TypeNode* type);

        /// returns named node from scope
        NamedNode* get(const Identifier& name);

        void generate(ModuleRef module);
    protected:
        std::map<Identifier, VariableNode*> m_vars;

        FunctionNode* o_owner;
        ScopeNode* o_parent;
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