/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_LANG_TYPENODE_INTERNAL
#define KIWI_LANG_TYPENODE_INTERNAL

#include "kiwi/config.hpp"
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
        virtual TypePtr get(Driver& driver) =0;
    protected:
        TypeNode();
    };

    /// Type node for internal types
    class ConcreteTypeNode : public TypeNode {
    public:
        /// constructor
        ConcreteTypeNode(TypePtr type);

        /// get type
        virtual TypePtr get(Driver& driver) {
            return m_type;
        }
    protected:
        TypePtr m_type;
    };

    class QualifiedTypeNode : public TypeNode {
    public:
        /// constructor
        QualifiedTypeNode(const Identifier& name);

        /// get type
        virtual TypePtr get(Driver& driver);
    protected:
        Identifier m_name;
    };
}}

#endif
