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
    getMetadata().fields().inherit(field);
}

// inherit method signal handler
void InsertMethodListener::operator()(Method* method) {
    getMetadata().methods().inherit(method);
}

//==------------------------------------------------------------------------==//

// constructor
TypeImpl::TypeImpl(Type* owner)
: m_owner(owner), varType(0), addressMap(0), virtualTable(0) {
    m_fields   = new MemberSet<Field>(owner);
    m_methods  = new MemberSet<Method>(owner);
    m_unary    = new MemberSet<UnaryOperator>(owner);
    m_binary   = new MemberSet<BinaryOperator>(owner);
    m_multiary = new MemberSet<MultiaryOperator>(owner);
}

// destructor
TypeImpl::~TypeImpl() {
    delete m_fields;
    delete m_methods;
    delete m_unary;
    delete m_binary;
    delete m_multiary;
}

void TypeImpl::insertBase(Type* type) {
    TypeImpl* parentImpl = type->getMetadata();
    for (std::set<Type*>::iterator i = parentImpl->m_bases.begin(); i != parentImpl->m_bases.end(); ++i) {
        insertBase(*i);
    }

    std::pair<std::set<Type*>::const_iterator, bool> result = m_bases.insert(type);
    if (result.second) {
        TypeImpl* meta = type->getMetadata();

        // inherit tables
        fields().inherit(meta->fields());
        methods().inherit(meta->methods());

        // merge already existes members from base type

    }
}

bool TypeImpl::isBase(const Type* type) const {
    return std::find(m_bases.begin(), m_bases.end(), type) != m_bases.end();
}
