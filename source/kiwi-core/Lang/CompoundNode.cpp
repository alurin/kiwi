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
: CompoundNode(type) { }


// append member
void CompoundNode::append(MemberNode* member) {
    m_members.push_back(member);
}

void ClassNode::generate(Driver& driver) {
    m_type = ObjectType::create(driver.getModule(), m_name);
    CompoundNode::generate(driver);
}

void CompoundNode::generate(Driver& driver) {
    assert(m_type && "Type not generated");

    /// Generate members
    for (std::vector<lang::MemberNode*>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
        (*i)->generate(driver, m_type);
    }

    /// Emit type structure
    m_type->emit();
}

// Emit type structure and methods
void CompoundNode::emit(Driver& driver) {
    assert(m_type && "Type not generated");

    /// Generate members
    for (std::vector<lang::MemberNode*>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
        (*i)->emit(driver, m_type);
    }
}
