/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_TYPEIMPL_INTERNAL
#define KIWI_TYPEIMPL_INTERNAL

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
        void inherit(const MemberSet<T>& members);

        /// return iterator pointed to begin
        const_iterator begin() const {
            return m_members.begin();
        }

        /// return iterator pointed to end
        const_iterator end() const {
            return m_members.end();
        }
    private:
        /// Owner for this implementation
        Type* m_owner;

        /// set of members
        std::set<T*> m_members;
    };

    ///
    class TypeImpl {
        friend class Type;
    public:
        /// Signal for insert new field
        boost::signals2::signal<void (Field*)> onInsertField;

        /// Singal for insert new method
        boost::signals2::signal<void (Method*)> onInsertMethod;

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

    // insert member
    template<typename T>
    T* MemberSet<T>::find(T* inherit) const {
        return 0;
    }

    // insert member
    template<typename T, typename C>
    T* find_if(const MemberSet<T>& members, const C& value) {
        typename MemberSet<T>::const_iterator it = std::find_if(members.begin(), members.end(), value);
        return (it != members.end()) ? *it : 0;
    }

    // insert member
    template<typename T>
    void MemberSet<T>::insert(T* member) {
        m_members.insert(member);
    }

    // merge inherit field in declare field
    template<typename T>
    void MemberSet<T>::merge(T* declare, T* inherit) {
        // erase override from already declared field
        T* exists = find(inherit);
        if (exists) {
            exists->unoverride(inherit);
            if (!exists->isDeclared() && !exists->isOverride()) {
                m_members.erase(exists);
                delete exists;
            }
        }

        // override existed member
        declare->override(inherit);
    }

    // inherit member
    template<typename T>
    void MemberSet<T>::inherit(T* member) {
        if (!find(member)) {
            T* member = new T(m_owner, member); // create clone
            m_members.insert(member);
        }
    }

    template<typename T>
    void MemberSet<T>::inherit(const MemberSet<T>& members) {
        for (const_iterator i = members.begin(); i != members.end(); ++i) {
            inherit(*i);
        }
    }
}

#endif
