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
}

namespace kiwi {
    class Field;
    class Method;
    class Type;
    class Callable;

    /// Member set for members
    template<typename T>
    class MemberSet {
    public:
        /// constructor
        MemberSet(Type* owner);

        /// insert member
        void insert(T* member);

        /// merge inherit field in declare field
        Field* find(Field* inherit);

        /// merge inherit field in declare field
        void merge(Field* declare, Field* inherit);
    protected:
        /// inherit member
        void inherit(T* member);

    private:
        /// Owner for this implementation
        Type* m_owner;

        /// set of members
        std::set<T*> m_members;
    };

    ///
    class TypeImpl {
    public:
        /// Signal for insert new field
        boost::signals2::signal<void (Field* field)> onInsertField;

        /// Singal for insert new method
        boost::signals2::signal<void (Method* callable)> onInsertMethod;

        /// LLVM analog
        llvm::Type* m_varType;

        /// Constructor
        TypeImpl(Type* owner);

        /// insert base type
        void insertBase(Type* type);
    protected:
        /// Owner for this implementation
        Type* m_owner;

        /// set of all based types [ struct and objects ]
        std::set<Type*> m_bases;

        /// set of fields
        MemberSet<Field> m_fields;

        /// set of methods
        MemberSet<Method> m_methods;

        /// set of unary operators
        MemberSet<UnaryOperator> m_unary;

        /// set of binary operators
        MemberSet<BinaryOperator> m_binary;

        /// set of multiary operators
        MemberSet<MultiaryOperator> m_multiary;
    };
}

#endif
