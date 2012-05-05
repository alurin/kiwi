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
        TypeListener(TypePtr owner);

        /// deference implementation
        TypeImpl& getMetadata() {
            return *m_owner->getMetadata();
        }
    private:
        TypePtr m_owner;
    };

    /// Inherit field listener for fields
    class InsertFieldListener : protected TypeListener {
    public:
        /// constructor
        InsertFieldListener(TypePtr owner);

        /// signal handler
        void operator()(FieldPtr field);
    };

    /// Inherit field listener for methods
    class InsertMethodListener : protected TypeListener {
    public:
        /// constructor
        InsertMethodListener(TypePtr owner);

        /// signal handler
        void operator()(MethodPtr method);
    };
}

// constructor
TypeListener::TypeListener(TypePtr owner) : m_owner(owner) {
}

// constructor
InsertFieldListener::InsertFieldListener(TypePtr owner) : TypeListener(owner) {
}

// constructor
InsertMethodListener::InsertMethodListener(TypePtr owner) : TypeListener(owner) {
}

// inherit field signal handler
void InsertFieldListener::operator()(FieldPtr field) {
    getMetadata().fields().inherit(field);
}

// inherit method signal handler
void InsertMethodListener::operator()(MethodPtr method) {
    getMetadata().methods().inherit(method);
}

//==------------------------------------------------------------------------==//

// constructor
TypeImpl::TypeImpl(Type* owner)
: m_owner(owner), varType(0), m_addressMap(), m_virtualTable() {
    m_addressMap   = new AddressMap(owner->getModule());
    m_virtualTable = new VirtualTable();
    m_fields       = new MemberSet<Field>(owner);
    m_methods      = new MemberSet<Method>(owner);
}

// destructor
TypeImpl::~TypeImpl() {
    delete m_fields;
    delete m_methods;
    delete m_addressMap;
    delete m_virtualTable;
}

void TypeImpl::insertBase(TypePtr type) {
    TypeImpl* parentImpl = type->getMetadata();
    for (std::set<TypePtr>::iterator i = parentImpl->m_bases.begin(); i != parentImpl->m_bases.end(); ++i) {
        insertBase(*i);
    }

    std::pair<std::set<TypePtr>::const_iterator, bool> result = m_bases.insert(type);
    if (result.second) {
        TypeImpl* meta = type->getMetadata();

        // inherit tables
        fields().inherit(meta->fields());
        methods().inherit(meta->methods());
    }
}

bool TypeImpl::isBase(const TypePtr type) const {
    return std::find(m_bases.begin(), m_bases.end(), type) != m_bases.end();
}
