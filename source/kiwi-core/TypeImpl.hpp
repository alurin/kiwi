/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_TYPEIMPL_INTERNAL
#define KIWI_TYPEIMPL_INTERNAL

#include "kiwi/config.hpp"
#include <boost/signals2.hpp>
// #include <vector>
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
        typedef typename std::set<T*>::const_iterator const_iterator;

        /// constructor
        MemberSet(Type* owner);

        /// insert member
        void insert(T* member);

        /// find field by base member
        T* find(T* inherit) const;

        /// merge inherit field in declare field
        void merge(T* declare, T* inherit);

        /// inherit member
        void inherit(T* member);

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
        std::set<T*> m_members;

        /// Signal for insert new field
        boost::signals2::signal<void (T*)> onInsert;

        /// Signal for insert new field
        boost::signals2::signal<void (T*)> onRemove;
    };

//==------------------------------------------------------------------------==//

    // Listener for insert inherited members
    template<typename T>
    class InsertMember {
    public:
        InsertMember(MemberSet<T>& members);

        void operator()(T* member);
    protected:
        MemberSet<T>& m_members;
    };

//==------------------------------------------------------------------------==//

    // Listener for remove inherited members
    template<typename T>
    class RemoveMember {
    public:
        RemoveMember(MemberSet<T>& members);

        void operator()(T* member);
    protected:
        MemberSet<T>& m_members;
    };

//==------------------------------------------------------------------------==//

    template<typename T>
    class OverridePredicate {
    public:
        OverridePredicate(T* member);

        bool operator()(T* member);
    protected:
        T* m_member;
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
        void insertBase(Type* type);

        /// insert base type
        bool isBase(const Type* type) const;

        MemberSet<Field>& fields() const {
            return *m_fields;
        }
        MemberSet<Method>& methods() const {
            return *m_methods;
        }
        MemberSet<UnaryOperator>& unary() const {
            return *m_unary;
        }
        MemberSet<BinaryOperator>& binary() const {
            return *m_binary;
        }
        MemberSet<MultiaryOperator>& multiary() const {
            return *m_multiary;
        }


        std::set<Type*>::const_iterator base_begin() const {
            return m_bases.begin();
        }
        std::set<Type*>::const_iterator base_end() const {
            return m_bases.end();
        }
    protected:
        /// Owner for this implementation
        Type* m_owner;

        /// set of all based types [ struct and objects ]
        std::set<Type*> m_bases;

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
    T* find_if(const MemberSet<T>& members, const C& value) {
        typename MemberSet<T>::const_iterator it = std::find_if(members.begin(), members.end(), value);
        return (it != members.end()) ? *it : 0;
    }

    // find member by name
    template<typename T>
    T* MemberSet<T>::find(T* inherit) const {
        return find_if(*this, OverridePredicate<T>(inherit));
    }

    // insert member
    template<typename T>
    void MemberSet<T>::insert(T* member) {
        m_members.insert(member);
        onInsert(member);
    }

    // merge inherit field in declare field
    template<typename T>
    void MemberSet<T>::merge(T* declare, T* inherit) {
        // erase override from already declared field
        T* exists = find(inherit);
        if (exists == declare) {
            // alredy merged
            return ;
        } else if (exists) {
            exists->unoverride(inherit);
            if (!(exists->isDeclared() || exists->isOverride())) {
                m_members.erase(exists);
                onRemove(exists);
                delete exists;
            }
        }

        // override existed member
        declare->override(inherit);
    }

    // inherit member
    template<typename T>
    void MemberSet<T>::inherit(T* member) {
        T* exists = find(member);
        if (!exists) {
            T* newf = new T(m_owner, member); // create clone
            m_members.insert(newf);
        }
    }

    // inherit members
    template<typename T>
    void MemberSet<T>::inherit(MemberSet<T>& members) {
        members.onInsert.connect(InsertMember<T>(*this));
        members.onRemove.connect(RemoveMember<T>(*this));
        for (const_iterator i = members.begin(); i != members.end(); ++i) {
            T* member = *i;
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
    void InsertMember<T>::operator()(T* member) {
        m_members.inherit(member);
    }

//==------------------------------------------------------------------------==//

    template<typename T>
    RemoveMember<T>::RemoveMember(MemberSet<T>& members)
    : m_members(members) {
    }

    template<typename T>
    void RemoveMember<T>::operator()(T* member) {
        // m_members.erase(member);
    }

//==------------------------------------------------------------------------==//

    template<typename T>
    OverridePredicate<T>::OverridePredicate(T* member)
    : m_member(member) {
    }

    template<typename T>
    bool OverridePredicate<T>::operator()(T* member) {
        return member->isOverride(m_member);
    }
}

#endif
