/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "TypeImpl.hpp"
#include "ModuleImpl.hpp"
#include "ContextImpl.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/Support/Iterator.hpp"
#include "Codegen/Emitter.hpp"
#include <llvm/Module.h>
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

using namespace kiwi;

namespace {
    class MethodComplete {
    public:
        MethodComplete(TypeImpl* type);

        void operator()(MethodPtr method);
    private:
        TypeImpl* m_meta;
    };
}

MethodComplete::MethodComplete(TypeImpl* meta)
: m_meta(meta) {
}

void MethodComplete::operator()(MethodPtr method) {
    MethodPtr declared = m_meta->getMethods().find(method);

    /// @todo This is bug?? Because declared must have self body
    if (declared) {
        declared->complete();
    }
}

// constructor
TypeImpl::TypeImpl(Type* owner, ModulePtr module)
: m_owner(owner), m_backendVariableType(0) , m_backendThisType(0)
, m_thisConverter(0), m_backendPointer(0), m_virtualTable(0), m_addressMap(0)
, m_fields(0), m_methods(0), m_ancestors(0) {
    llvm::Module* backendModule = module->getMetadata()->getBackendModule();
    llvm::LLVMContext& context  = backendModule->getContext();

    // create pointer to type
    llvm::Type* pointerType       = llvm::Type::getInt8Ty(context);
    m_backendPointer              = new llvm::GlobalVariable(*backendModule, pointerType, false, llvm::GlobalValue::ExternalLinkage, 0, "::_type");

    // map pointer to type
    ContextImpl* meta             = module->getContext()->getMetadata();
    llvm::ExecutionEngine* engine = meta->getBackendEngine();
    engine->addGlobalMapping(m_backendPointer, owner);
}

// destructor
TypeImpl::~TypeImpl() {
    delete m_thisConverter;
    delete m_fields;
    delete m_methods;
    delete m_ancestors;
    delete m_virtualTable;
    delete m_addressMap;
}

bool TypeImpl::addAncestor(AncestorPtr ancestor) {
    if (getAncestors().insert(ancestor)) {
        TypeImpl* meta = ancestor->getAncestorType()->getMetadata();
        getFields().inherit(meta->getFields());
        getMethods().inherit(meta->getMethods());
        onMethodComplete.connect(MethodComplete(this));
        return true;
    }
    return false;
}

bool TypeImpl::isAncestor(const TypePtr type) const {
    if (m_ancestors) {
        return m_ancestors->find(type).get() != 0;
    }
    return false;
}


// return information about virtual table and address map for original type
AncestorMetadata* TypeImpl::getAncestorMetadata(TypePtr type) {
    if (m_ancestors) {
        AncestorPtr ancestor = m_ancestors->find(type);
        if (ancestor) {
            return ancestor->getMetadata();
        }
    }

    BOOST_THROW_EXCEPTION(Exception() << exception_message("Received type is not base for current type"));
}

// return set of fields
MemberSet<Field>& TypeImpl::getFields() const {
    if (!m_fields) {
        m_fields = new MemberSet<Field>(m_owner);
    }
    return *m_fields;
}

// return set of methods
MemberSet<Method>& TypeImpl::getMethods() const {
    if (!m_methods) {
        m_methods = new MemberSet<Method>(m_owner);
    }
    return *m_methods;
}

// return map of accestors
AncestorMap& TypeImpl::getAncestors() const {
    if (!m_ancestors) {
        m_ancestors = new AncestorMap(m_owner);
    }
    return *m_ancestors;
}

// returns virtual table
StaticVirtualTable& TypeImpl::getVirtualTable() const {
    if (!m_virtualTable) {
        m_virtualTable = new StaticVirtualTable(getOwner());
        m_virtualTable->update();
    }
    return *m_virtualTable;
}

// returns address map
StaticAddressMap& TypeImpl::getAddressMap() const {
    if (!m_addressMap) {
        m_addressMap = new StaticAddressMap(getOwner());
        m_addressMap->update();
    }
    return *m_addressMap;
}
