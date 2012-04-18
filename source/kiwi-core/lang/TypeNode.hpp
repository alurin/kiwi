#ifndef KIWI_LANG_TYPENODE_INTERNAL
#define KIWI_LANG_TYPENODE_INTERNAL

#include "kiwi/Config.hpp"
#include "Node.hpp"

namespace kiwi
{
    typedef boost::shared_ptr<class Type>    TypeRef;
    typedef boost::shared_ptr<class Context> ContextRef;

namespace lang
{
    /// Type node
    class TypeNode : public Node
    {
    public:
        /// destructor
        virtual ~TypeNode();

        /// get type
        virtual TypeRef get() =0;

    protected:
        TypeNode();
    };

    /// Type node for internal types
    class ConcreteTypeNode : public TypeNode {
    public:
        /// constructor
        ConcreteTypeNode(TypeRef type);

        /// get type
        virtual TypeRef get()
        {
            return m_type;
        }
    protected:
        TypeRef m_type;
    };

    /// Type factory for parser
    class TypeFactory
    {
    public:
        TypeFactory(ContextRef context);

        TypeNode* getVoid();

        TypeNode* getInt();

        TypeNode* getString();

        TypeNode* getArray(TypeNode* type);

    protected:
        ContextRef m_context;
    };

}}

#endif