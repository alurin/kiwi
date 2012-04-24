#ifndef KIWI_LANG_TYPENODE_INTERNAL
#define KIWI_LANG_TYPENODE_INTERNAL

#include "kiwi/Config.hpp"
#include "Node.hpp"

namespace kiwi {
    class Type;
    class Context;

namespace lang {
    class Driver;

    /// Type node
    class TypeNode : public Node {
    public:
        /// destructor
        virtual ~TypeNode();

        /// get type
        virtual Type* get(Driver& driver) =0;
    protected:
        TypeNode();
    };

    /// Type node for internal types
    class ConcreteTypeNode : public TypeNode {
    public:
        /// constructor
        ConcreteTypeNode(Type* type);

        /// get type
        virtual Type* get(Driver& driver) {
            return m_type;
        }
    protected:
        Type* m_type;
    };

    class QualifiedTypeNode : public TypeNode {
    public:
        /// constructor
        QualifiedTypeNode(const Identifier& name);

        /// get type
        virtual Type* get(Driver& driver);
    protected:
        Identifier m_name;
    };
}}

#endif
