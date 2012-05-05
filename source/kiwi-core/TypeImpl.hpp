/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_TYPEIMPL_INTERNAL
#define KIWI_TYPEIMPL_INTERNAL

#include "kiwi/Type.hpp"
#include <boost/signals2.hpp>
#include <set>

namespace llvm {
    class Type;
    class GlobalVariable;
}

namespace kiwi {
    class Field;
    class Method;
    class Type;
    class Callable;
    class UnaryOperator;
    class BinaryOperator;
    class MultiaryOperator;

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

    /// Storage for internal members of type
    class TypeImpl {
        friend class Type;
    public:
        /// LLVM analog
        llvm::Type* varType;

        /// LLVM analog for address map
        llvm::GlobalVariable* addressMap;

        /// LLVM analog for virtual table
        llvm::GlobalVariable* virtualTable;

        /// insert base type
        void insertBase(TypePtr type);

        /// insert base type
        bool isBase(const TypePtr type) const;

        /// return set of fields
        MemberSet<Field>& fields() const {
            return *m_fields;
        }

        /// return set of methods
        MemberSet<Method>& methods() const {
            return *m_methods;
        }

        /// return set of unary operators
        MemberSet<UnaryOperator>& unary() const {
            return *m_unary;
        }

        /// return set of binary operators
        MemberSet<BinaryOperator>& binary() const {
            return *m_binary;
        }

        /// return set of multiary operators
        MemberSet<MultiaryOperator>& multiary() const {
            return *m_multiary;
        }

        /// return iterator pointed for begin of bases
        std::set<TypePtr>::const_iterator base_begin() const {
            return m_bases.begin();
        }

        /// return iterator pointed after end of bases
        std::set<TypePtr>::const_iterator base_end() const {
            return m_bases.end();
        }
    protected:
        /// Owner for this implementation
        Type* m_owner;

        /// set of all based types [ struct and objects ]
        std::set<TypePtr> m_bases;

        /// set of fields
        MemberSet<Field>* m_fields;

        /// set of methods
        MemberSet<Method>* m_methods;

        /// set of unary operators
        MemberSet<UnaryOperator>* m_unary;

        /// set of binary operators
        MemberSet<BinaryOperator>* m_binary;

        /// set of multiary operators
        MemberSet<MultiaryOperator>* m_multiary;
    private:
        /// Constructor
        TypeImpl(Type* owner);

        /// destructor
        ~TypeImpl();
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
