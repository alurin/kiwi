/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Driver.hpp"
#include "CompoundNode.hpp"
#include "MemberNode.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/DerivedTypes.hpp"
#include "kiwi/Support/Cast.hpp"

using namespace kiwi;
using namespace kiwi::lang;

// internal constructor
CompoundNode::CompoundNode()
: m_type() {
}

// internal constructor
CompoundNode::CompoundNode(TypePtr type)
: m_type(type) {
}

// remove nodes
CompoundNode::~CompoundNode() {
    for (std::vector<MemberNode*>::iterator i = m_members.begin(); i != m_members.end(); ++i) {
        MemberNode* member = *i;
        delete member;
    }
}

// constructor
ClassNode::ClassNode(const Identifier& name) : m_name(name) {
}

// constructor
ConcreteClassType::ConcreteClassType(TypePtr type)
: CompoundNode(type) {
}


// append member
void CompoundNode::append(MemberNode* member) {
    m_members.push_back(member);
}

void ClassNode::generateType(Driver& driver) {
    ObjectPtr current;
    m_type = current = ObjectType::create(driver.getModule(), m_name);

    for (std::vector<Identifier>::iterator i = m_inherits.begin(); i != m_inherits.end(); ++i) {
        TypePtr type = driver.getModule()->find(*i);
        if (ObjectPtr parent = dyn_cast<ObjectType>(type)) {
            current->inherit(parent);
        } else if (type) {
            BOOST_THROW_EXCEPTION(LangException()
                << exception_format("Type '%1%' is not class", m_name)
                << exception_location(to_location(this)));
        } else {
            BOOST_THROW_EXCEPTION(LangException()
                << exception_format("Type '%1%' not found", m_name)
                << exception_location(to_location(this)));
        }
    }
}

void CompoundNode::generateType(Driver& driver) {
    /* empty for default */
}

void CompoundNode::generateMembers(Driver& driver) {
    kiwi_assert(m_type, "Type not generated");

    /// Generate members
    for (std::vector<lang::MemberNode*>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
        (*i)->generateMember(driver, m_type);
    }

    /// Update structure
    m_type->update();
}

// Emit IR signature
void CompoundNode::generateIRSignature(Driver& driver) {
    kiwi_assert(m_type, "Type not generated");

    /// Generate members
    for (std::vector<lang::MemberNode*>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
        (*i)->generateIRSignature(driver, m_type);
    }
}

// Emit IR bytecode
void CompoundNode::generateIRCode(Driver& driver) {
    kiwi_assert(m_type, "Type not generated");

    /// Generate members
    for (std::vector<lang::MemberNode*>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
        (*i)->generateIRCode(driver, m_type);
    }
}
