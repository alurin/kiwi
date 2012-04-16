#ifndef KIWI_LANG_FUNCTIONNODE_INTERNAL
#define KIWI_LANG_FUNCTIONNODE_INTERNAL

#include "kiwi/Config.hpp"
#include "Node.hpp"
#include <map>

namespace kiwi { namespace lang {
    class TypeNode;
    class FunctionNode;
    class LeftNode;
    class RightNode;
    class ScopeNode;

    class ArgumentNode
    {
    public:
        ArgumentNode(FunctionNode* owner, const Identifier& name, TypeNode* type);

        virtual ~ArgumentNode();
    protected:
        FunctionNode* o_owner;
        Identifier    m_name;
        TypeNode*     m_type;
    };

    class VariableNode : public Node
    {
    public:
        VariableNode(ScopeNode* owner, const Identifier& name, TypeNode* type);

        virtual ~VariableNode();
        LeftNode* getLeft();
        RightNode* getRight();
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
        void declare(const Identifier& name, TypeNode* type);

        ///
        VariableNode* get(const Identifier& name);
    protected:
        std::map<Identifier, VariableNode*> m_vars;

        FunctionNode* o_owner;
        ScopeNode* o_parent;
    };

    class FunctionNode : public Node //, public VairableStorage
    {
    public:
        /// construct function node
        FunctionNode(const Identifier& name, TypeNode* type);

        /// destructor
        virtual ~FunctionNode();

        /// declare function argument
        ArgumentNode* declare(const Identifier& name, TypeNode* type);

        /// Returns root scope
        ScopeNode* getRoot() const {
            return m_root;
        }

        void dump();
    protected:
        Identifier      m_name;
        TypeNode*       m_type;
        ScopeNode*      m_root;

        std::map<Identifier, ArgumentNode*> m_args;
    };

}}

#endif