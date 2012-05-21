/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "VirtualTable.hpp"
#include "DynamicTable.cpp"
#include "../TypeImpl.hpp"
#include "kiwi/Members.hpp"

using namespace kiwi;

namespace {
    /// New methods listeners
    class MethodInsert {
    public:
        /// constructor
        MethodInsert(StaticVirtualTable* vtable);

        /// handler
        void operator()(MethodPtr method);
    protected:
        /// vtable
        StaticVirtualTable* m_vtable;
    };

    /// Override methods listeners
    class MethodOverride {
    public:
        /// constructor
        MethodOverride(UpcastVirtualTable* vtable);

        /// handler
        void operator()(MethodPtr method, MethodPtr inherit);
    protected:
        /// vtable
        UpcastVirtualTable* m_vtable;
    };

    /// Change method body listener
    class MethodComplete {
    public:
        // constructor
        MethodComplete(VirtualTable* vtable);

        /// handler
        void operator()(MethodPtr method);
    protected:
        /// vtable
        VirtualTable* m_vtable;
    };

    /// Change method body listener
    class MethodOverrideComplete {
    public:
        // constructor
        MethodOverrideComplete(UpcastVirtualTable* vtable);

        /// handler
        void operator()(MethodPtr method);
    protected:
        /// vtable
        UpcastVirtualTable* m_vtable;
    };
}

MethodInsert::MethodInsert(StaticVirtualTable* vtable)
: m_vtable(vtable) {
}

MethodOverride::MethodOverride(UpcastVirtualTable* vtable)
: m_vtable(vtable) {
}

MethodComplete::MethodComplete(VirtualTable* vtable)
: m_vtable(vtable) {
}

MethodOverrideComplete::MethodOverrideComplete(UpcastVirtualTable* vtable)
: m_vtable(vtable) {
}

VirtualTable::VirtualTable(TypePtr type, ModulePtr module)
: m_type(type), m_module(), m_dtable(module) {

}

// constructor
StaticVirtualTable::StaticVirtualTable(TypePtr owner)
: VirtualTable(owner, owner->getModule()) {
    TypeImpl* meta = owner->getMetadata();
    meta->getMethods().onInsert.connect(MethodInsert(this));
    meta->onMethodComplete.connect(MethodComplete(this));
}

// constructor
UpcastVirtualTable::UpcastVirtualTable(TypePtr ancestor, TypePtr derived)
: VirtualTable(ancestor, derived->getModule()), m_derived(derived) {
    TypeImpl* meta = derived->getMetadata();
    meta->getMethods().onOverride.connect(MethodOverride(this));
    meta->onMethodComplete.connect(MethodOverrideComplete(this));
}

llvm::GlobalVariable* VirtualTable::getBackendVariable() const {
    return m_dtable.getBackendVariable();
}

void* VirtualTable::getPointer() const {
    return m_dtable.getPointer();
}

// returns size of address map
size_t VirtualTable::size() const {
    return m_dtable.size();
}

// update vtable
void StaticVirtualTable::update() {
    TypeImpl* meta = getType()->getMetadata();
    MemberSet<Method>& methods = meta->getMethods();
    if (methods.size() != 0) {
        m_dtable.resize(meta->getMethods().size());
        for (MemberSet<Method>::const_iterator i = methods.begin(); i != methods.end(); ++i) {
            MethodPtr method = *i;
            updateSlot(method);
        }
    }
}

// update vtable
void UpcastVirtualTable::update() {
    TypeImpl* meta = getType()->getMetadata();
    MemberSet<Method>& methods = meta->getMethods();
    if (methods.size() != 0) {
        MemberSet<Method>& overrides = getDerivedType()->getMetadata()->getMethods();
        m_dtable.resize(meta->getMethods().size());
        for (MemberSet<Method>::const_iterator i = methods.begin(); i != methods.end(); ++i) {
            MethodPtr method = *i;
            MethodPtr override = overrides.find(method);
            updateSlot(method, override->getPointerTo());
        }
    }
}

// update method in vtable
void VirtualTable::updateSlot(MethodPtr method, void* px) {
    int32_t idx = method->getPosition();
    px = px ?: method->getPointerTo();

    if (idx >= m_dtable.size()) {
        m_dtable.resize(idx * 1.6);
    } else if (m_dtable.size() == 0) {
        m_dtable.resize(3);
    }
    m_dtable[idx] = px;
}

// insert method in vtable
void StaticVirtualTable::insertSlot(MethodPtr method) {
    if (method->m_position == -1) { // guard from recursion
        method->m_position = m_dtable.nextPosition();
    }
}

// handler
void MethodInsert::operator()(MethodPtr method) {
    m_vtable->updateSlot(method);
}

// handler
// @todo testes
void MethodOverride::operator()(MethodPtr method, MethodPtr inherit) {
    if (inherit->getOwnerType() == m_vtable->getType()) {
        m_vtable->updateSlot(inherit, method->getPointerTo());
    }
}

// handler
void MethodComplete::operator()(MethodPtr method) {
    m_vtable->updateSlot(method);
}

// handler
// @todo testes
void MethodOverrideComplete::operator()(MethodPtr method) {
    MemberSet<Method>& overrides = m_vtable->getDerivedType()->getMetadata()->getMethods();
    MethodPtr override = overrides.find(method);
    if (override && method->getOwnerType() == m_vtable->getType()) {
        m_vtable->updateSlot(method, override->getPointerTo());
    }
}
