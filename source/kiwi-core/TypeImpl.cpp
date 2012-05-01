/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "TypeImpl.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"

using namespace kiwi;

namespace {
    /// Base listener for type signals
    class TypeListener {
    public:
        /// constructor
        TypeListener(Type* owner);

        /// deference implementation
        TypeImpl& getMetadata() {
            return *m_owner->getMetadata();
        }
    private:
        Type* m_owner;
    };

    /// Inherit field listener for fields
    class InsertFieldListener : protected TypeListener {
    public:
        /// constructor
        InsertFieldListener(Type* owner);

        /// signal handler
        void operator()(Field* field);
    };

    /// Inherit field listener for methods
    class InsertMethodListener : protected TypeListener {
    public:
        /// constructor
        InsertMethodListener(Type* owner);

        /// signal handler
        void operator()(Method* method);
    };
}

// constructor
TypeListener::TypeListener(Type* owner) : m_owner(owner) {
}

// constructor
InsertFieldListener::InsertFieldListener(Type* owner) : TypeListener(owner) {
}

// constructor
InsertMethodListener::InsertMethodListener(Type* owner) : TypeListener(owner) {
}

// inherit field signal handler
void InsertFieldListener::operator()(Field* field) {
    getMetadata().inherit(field);
}

// inherit method signal handler
void InsertMethodListener::operator()(Method* method) {
    getMetadata().inherit(method);
}

//==------------------------------------------------------------------------==//

/// constructor
template<typename T>
MemberSet<T>::MemberSet(Type* owner) : m_owner(owner) {
}

// insert member
template<typename T>
void MemberSet<T>::insert(T* member) {
    m_members.insert(member);
    // onInsertField(member);
}

// merge inherit field in declare field
template<typename T>
void MemberSet<T>::merge(Field* declare, Field* inherit) {
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
        T* member = T::clone(m_owner, member); /// clone member
        m_members.insert(member);
    }
}

//==------------------------------------------------------------------------==//

// constructor
TypeImpl::TypeImpl(Type* owner) : MemberSet<Field>(owner), MemberSet<Method>(owner), m_owner(owner) {
}

void TypeImpl::insertBase(Type* type) {
    std::pair<std::set<Type*>::const_iterator, bool> result = m_bases.insert(type);
    if (result.second) {
        TypeImpl* meta = type->getMetadata();

        // connect to signals from base type
        meta->onInsertField.connect(InsertFieldListener(m_owner));
        meta->onInsertMethod.connect(InsertMethodListener(m_owner));

        // merge already existes members from base type

    }
}
