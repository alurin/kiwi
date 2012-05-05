/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_MEMBERSET_INTERNAL
#define KIWI_SUPPORT_MEMBERSET_INTERNAL

#include "kiwi/types.hpp"
#include <boost/signals2.hpp>
#include <set>

namespace kiwi {

//==------------------------------------------------------------------------==//

    /// Member set for members
    template<typename T>
    class MemberSet {
    public:
        /// typedef for smart pointers of type
        typedef typename boost::shared_ptr<T> reference;

        typedef typename std::set<reference>::const_iterator const_iterator;

        /// constructor
        MemberSet(Type* owner);

        /// insert member
        void insert(reference member);

        /// find field by base member
        reference find(reference inherit) const;

        /// merge inherit field in declare field
        void merge(reference declare, reference inherit);

        /// inherit member
        void inherit(reference member);

        /// merge members from other member set
        void inherit(MemberSet<T>& members);

        /// return iterator pointed to begin
        const_iterator begin() const {
            return m_members.begin();
        }

        /// return iterator pointed to end
        const_iterator end() const {
            return m_members.end();
        }

        /// return size
        size_t size() const {
            return m_members.size();
        }
    private:
        /// Owner for this implementation
        Type* m_owner;

        /// set of members
        std::set<reference> m_members;

        /// Signal for insert new field
        boost::signals2::signal<void (reference)> onInsert;

        /// Signal for insert new field
        boost::signals2::signal<void (reference)> onRemove;

        /// Signal for override field
        boost::signals2::signal<void (reference, reference)> onOverride;
    };

//==------------------------------------------------------------------------==//

    // Listener for insert inherited members
    template<typename T>
    class InsertMember {
    public:
        /// typedef for smart pointers of type
        typedef boost::shared_ptr<T> reference;

        /// constructor
        InsertMember(MemberSet<T>& members);

        /// event handler
        void operator()(reference member);
    protected:
        MemberSet<T>& m_members;
    };

//==------------------------------------------------------------------------==//

    // Listener for remove inherited members
    template<typename T>
    class RemoveMember {
    public:
        /// typedef for smart pointers of type
        typedef boost::shared_ptr<T> reference;

        /// constructor
        RemoveMember(MemberSet<T>& members);

        /// event handler
        void operator()(reference member);
    protected:
        MemberSet<T>& m_members;
    };

//==------------------------------------------------------------------------==//

    template<typename T>
    class OverridePredicate {
    public:
        /// typedef for smart pointers of type
        typedef boost::shared_ptr<T> reference;

        /// constructor
        OverridePredicate(reference member);

        /// predicate check
        bool operator()(reference member);
    protected:
        reference m_member;
    };

//==------------------------------------------------------------------------==//

    // constructor
    template<typename T>
    MemberSet<T>::MemberSet(Type* owner) : m_owner(owner) {
    }

    // find member by predicate
    template<typename T, typename C>
    typename MemberSet<T>::reference find_if(const MemberSet<T>& members, const C& value) {
        typename MemberSet<T>::const_iterator it = std::find_if(members.begin(), members.end(), value);
        return (it != members.end()) ? *it : typename MemberSet<T>::reference();
    }

    // find member by name
    template<typename T>
    typename MemberSet<T>::reference MemberSet<T>::find(reference inherit) const {
        return find_if(*this, OverridePredicate<T>(inherit));
    }

    // insert member
    template<typename T>
    void MemberSet<T>::insert(reference member) {
        m_members.insert(member);
        onInsert(member);
    }

    // merge inherit field in declare field
    template<typename T>
    void MemberSet<T>::merge(reference declare, reference inherit) {
        // erase override from already declared field
        reference exists = find(inherit);
        if (exists == declare) {
            // alredy merged
            return ;
        } else if (exists) {
            exists->unoverride(inherit);
            if (!(exists->isDeclared() || exists->isOverride())) {
                m_members.erase(exists);
                onRemove(exists);
            }
        }

        // override existed member
        declare->override(inherit);
        onOverride(declare, inherit);
    }

    // inherit member
    template<typename T>
    void MemberSet<T>::inherit(reference member) {
        reference exists = find(member);
        if (!exists) {
            reference newf = T::inherit(m_owner->shared_from_this(), member); // create clone
            m_members.insert(newf);
        }
    }

    // inherit members
    template<typename T>
    void MemberSet<T>::inherit(MemberSet<T>& members) {
        members.onInsert.connect(InsertMember<T>(*this));
        members.onRemove.connect(RemoveMember<T>(*this));
        for (const_iterator i = members.begin(); i != members.end(); ++i) {
            reference member = *i;
            if (member->isDeclared()) {
                inherit(member);
            }
        }
    }

//==------------------------------------------------------------------------==//

    template<typename T>
    InsertMember<T>::InsertMember(MemberSet<T>& members)
    : m_members(members) {
    }

    template<typename T>
    void InsertMember<T>::operator()(reference member) {
        m_members.inherit(member);
    }

//==------------------------------------------------------------------------==//

    template<typename T>
    RemoveMember<T>::RemoveMember(MemberSet<T>& members)
    : m_members(members) {
    }

    template<typename T>
    void RemoveMember<T>::operator()(reference member) {
        // m_members.erase(member);
    }

//==------------------------------------------------------------------------==//

    template<typename T>
    OverridePredicate<T>::OverridePredicate(reference member)
    : m_member(member) {
    }

    template<typename T>
    bool OverridePredicate<T>::operator()(reference member) {
        return member->isOverride(m_member);
    }
}

#endif
