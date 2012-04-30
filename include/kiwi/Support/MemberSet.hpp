#ifndef KIWI_SUPPORT_TABLE_INCLUDED
#define KIWI_SUPPORT_TABLE_INCLUDED

#include <set>
#include <algorithm>
#include "kiwi/assert.hpp"

namespace kiwi {
    class Type;

    /// Container for overridable members. This container managed memory of members
    /// containts in him
    template<typename TMember>
    class MemberSet {
    public:
        typedef typename std::set<TMember*> Set;
        typedef typename Set::iterator iterator;
        typedef typename Set::const_iterator const_iterator;

        /// constructor for set
        MemberSet(Type* owner);

        /// desturctor
        ~MemberSet();

        /// declare  member
        void insert(TMember* member);

        /// override all members from
        void merge(const MemberSet<TMember>& members);

        /// override member
        void merge(TMember* declared, TMember* inherited);

        /// find member, which overrides parent member
        TMember* find(TMember* declared) const;

        size_t size() const {
            return m_members.size();
        }

        iterator begin() {
            return m_members.begin();
        }

        const_iterator begin() const {
            return m_members.begin();
        }

        iterator end() {
            return m_members.end();
        }

        const_iterator end() const {
            return m_members.end();
        }

    private:
        Set     m_members;
        Type*   m_owner;
    };

    /// Predicate for search of child member, which overrides parent member
    template<typename TMember>
    class OverridablePredicate {
    public:
        /// constructor
        OverridablePredicate(TMember* parent) : parent(parent) {
        }

        /// check member overrides
        bool operator()(TMember* child) {
            return child->isOverride(parent);
        }
    private:
        /// parent member
        TMember* parent;
    };

    // constructor for set
    template<typename TMember>
    MemberSet<TMember>::MemberSet(Type* owner) : m_owner(owner) {
    }

    // desturctor
    template<typename TMember>
    MemberSet<TMember>::~MemberSet() {
        for (MemberSet<TMember>::const_iterator i = m_members.begin(); i != m_members.end(); ++i) {
            TMember* member  = *i;
            delete member;
        }
    }

     // override member
    template<typename TMember>
    TMember* MemberSet<TMember>::find(TMember* declared) const {
        const_iterator it = std::find_if( m_members.begin(), m_members.end(), OverridablePredicate<TMember>(declared));
        return (it == m_members.end() ? 0 : *it);
    }

    template<typename TMember>
    void MemberSet<TMember>::insert(TMember* member) {
        m_members.insert(member);
    }

    // override all members from
    template<typename TMember>
    void MemberSet<TMember>::merge(const MemberSet<TMember>& members) {
        for (MemberSet<TMember>::const_iterator i = members.begin(); i != members.end(); ++i) {
            TMember* member  = *i;
            if (0 == this->find(member)) {
                TMember* inherit = new TMember(m_owner, member);
                insert(inherit);
            }
        }
    }

    template<typename TMember>
    void MemberSet<TMember>::merge(TMember* declared, TMember* inherited) {
        TMember* current = find(inherited);
        if (declared == current) {
            return;
        } else if (current) {
            current->removeOverride(inherited);
            if (!current->isDeclared() && current->override_empty()) {
                m_members.erase(declared);
                delete declared;
            }
        }
        declared->override(inherited);
    }

}

#endif
