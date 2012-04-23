#ifndef KIWI_LANG_TYPENODE_INTERNAL
#define KIWI_LANG_TYPENODE_INTERNAL

#include "kiwi/Config.hpp"
#include "Node.hpp"

namespace kiwi {
    class Type;
    class Context;

namespace lang {
    /// Type node
    class TypeNode : public Node {
    public:
        /// destructor
        virtual ~TypeNode();

        /// get type
        virtual Type* get() =0;

    protected:
        TypeNode();
    };

    /// Type node for internal types
    class ConcreteTypeNode : public TypeNode {
    public:
        /// constructor
        ConcreteTypeNode(Type* type);

        /// get type
        virtual Type* get() {
            return m_type;
        }
    protected:
        Type* m_type;
    };

}}

#endif
