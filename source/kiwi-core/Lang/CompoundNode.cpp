#include "Driver.hpp"
#include "CompoundNode.hpp"
#include "MemberNode.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <assert.h>

using namespace kiwi;
using namespace kiwi::lang;

// internal constructor
CompoundNode::CompoundNode()
: m_type(0) {
}

// internal constructor
CompoundNode::CompoundNode(Type* type)
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
ConcreteClassType::ConcreteClassType(Type* type)
: CompoundNode(type) {
}


// append member
void CompoundNode::append(MemberNode* member) {
    m_members.push_back(member);
}

void ClassNode::generateType(Driver& driver) {
    m_type = ObjectType::create(driver.getModule(), m_name);
}

void CompoundNode::generateType(Driver& driver) {
    /* empty for default */
}

void CompoundNode::generateMembers(Driver& driver) {
    assert(m_type && "Type not generated");

    /// Generate members
    for (std::vector<lang::MemberNode*>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
        (*i)->generateMember(driver, m_type);
    }

    /// Emit type structure
    m_type->emit();
}

// Emit IR signature
void CompoundNode::generateIRSignature(Driver& driver) {
    assert(m_type && "Type not generated");

    /// Generate members
    for (std::vector<lang::MemberNode*>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
        (*i)->generateIRSignature(driver, m_type);
    }
}

// Emit IR bytecode
void CompoundNode::generateIRCode(Driver& driver) {
    assert(m_type && "Type not generated");

    /// Generate members
    for (std::vector<lang::MemberNode*>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
        (*i)->generateIRCode(driver, m_type);
    }
}
