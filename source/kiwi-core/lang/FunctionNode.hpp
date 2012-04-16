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

    class ScopeNode : public Node {
    public:
        ScopeNode(FunctionNode* parent);
        ScopeNode(ScopeNode* parent);

        LeftNode* getLeftLocal(const Identifier& name);

        LeftNode* getLeftInstance(const Identifier& name);

        RightNode* getRightLocal(const Identifier& name);

        RightNode* getRightInstance(const Identifier& name);
    protected:
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

        /// add function node argument
        ArgumentNode* add(const Identifier& name, TypeNode* type);

        /// Complete function
        void end();

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