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
        MethodComplete(Type* type);

        void operator()(MethodPtr method);
    private:
        Type* m_type;
    };
}

MethodComplete::MethodComplete(Type* type)
: m_type(type) {
}

void MethodComplete::operator()(MethodPtr method) {
    TypeImpl* meta     = m_type->getMetadata();
    MethodPtr declared = meta->methods().find(method);

    /// @todo This is bug?? Because declared must have self body
    if (declared) {
        declared->complete();
    }
}

// constructor
TypeImpl::TypeImpl(Type* owner, ModulePtr module)
: m_owner(owner), m_backendVariableType(0)
, m_backendThisType(0), m_thisConverter(0), m_backendPointer(0) {
    m_fields       = new MemberSet<Field>(owner);
    m_methods      = new MemberSet<Method>(owner);

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
    for (std::map<TypePtr, InheritanceInfo*>::const_iterator i = m_inheritances.begin(); i != m_inheritances.end(); ++i) {
        InheritanceInfo* info = i->second;
        delete info;
    }
    delete m_thisConverter;
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
        meta->onMethodComplete.connect(MethodComplete(m_owner));
    }
}

bool TypeImpl::isBase(const TypePtr type) const {
    return std::find(m_bases.begin(), m_bases.end(), type) != m_bases.end();
}

// return information about virtual table and address map for this type
InheritanceInfo* TypeImpl::getOriginalMetadata() {
    return getOriginalMetadata(m_owner->shared_from_this());
}

// return information about virtual table and address map for original type
InheritanceInfo* TypeImpl::getOriginalMetadata(TypePtr type) {
    if (m_owner == type.get() || isBase(type)) {
        std::map<TypePtr, InheritanceInfo*>::const_iterator result = m_inheritances.find(type);
        if (result == m_inheritances.end()) {
            InheritanceInfo* info = new InheritanceInfo(type.get(), m_owner);
            m_inheritances.insert(std::make_pair(type, info));
            return info;
        }
        return result->second;
    }

    BOOST_THROW_EXCEPTION(Exception() << exception_message("Received type is not base for current type"));
}
