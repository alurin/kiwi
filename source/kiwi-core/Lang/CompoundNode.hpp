/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_LANG_COMPOUNDNODE_INTERNAL
#define KIWI_LANG_COMPOUNDNODE_INTERNAL

#include "Node.hpp"
#include <vector>

namespace kiwi {
    class Type;
namespace lang {
    class MemberNode;
    class Driver;

    //==--------------------------------------------------------------------==//
    /// Base for member nodes
    class CompoundNode : public Node {
    public:
        /// remove nodes
        virtual ~CompoundNode();

        /// append member
        void append(MemberNode* member);

        /// void
        void inherit(const Identifier& name) {
            m_inherits.push_back(name);
        }

        /// void
        void implement(const Identifier& name) {

        }

        /// returns type
        TypePtr getType() const {
            return m_type;
        }

        /// generate types
        virtual void generateType(Driver& driver);

        /// generate members
        void generateMembers(Driver& driver);

        /// generate IR signature
        void generateIRSignature(Driver& driver);

        /// generate code
        void generateIRCode(Driver& driver);
    protected:
        /// Generated type
        TypePtr m_type;

        /// remove members
        std::vector<MemberNode*> m_members;

        /// remove members
        std::vector<Identifier> m_inherits;

        /// internal constructor
        CompoundNode();

        /// internal constructor
        CompoundNode(TypePtr type);
    }; // class CompoundNode

    //==--------------------------------------------------------------------==//
    /// Class definition
    class ClassNode : public CompoundNode {
    public:
        /// constructor
        ClassNode(const Identifier& name);

        /// Generate type, only create analogs
        virtual void generateType(Driver& driver);
    protected:
        /// Class name
        Identifier m_name;
    }; // class ClassNode

    //==--------------------------------------------------------------------==//
    /// Class definition node for existed classes
    class ConcreteClassType : public CompoundNode {
    public:
        /// constructor
        ConcreteClassType(TypePtr type);
    protected:
    }; // class ConcreteClassType
}} // namespace kiwi::lang

#endif
