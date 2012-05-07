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
#include "Codegen/Emitter.hpp"
#include <llvm/Module.h>
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/DerivedTypes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

using namespace kiwi;

// constructor
TypeImpl::TypeImpl(Type* owner, ModulePtr module)
: m_owner(owner), m_addressMap(), m_virtualTable(), m_backendVariableType(0)
, m_backendThisType(0), m_thisConverter(0), m_backendPointer(0) {
    m_addressMap   = new AddressMap(owner, module);
    m_virtualTable = new VirtualTable(owner, module);
    m_fields       = m_addressMap;   //new MemberSet<Field>(owner);
    m_methods      = m_virtualTable; //new MemberSet<Method>(owner);

    llvm::Module* backendModule = module->getMetadata()->getBackendModule();
    llvm::LLVMContext& context  = backendModule->getContext();

    // create pointer to type
    llvm::Type* pointerType       = llvm::Type::getInt8Ty(context);
    m_backendPointer              = new llvm::GlobalVariable(*backendModule, pointerType, false, llvm::GlobalValue::ExternalLinkage, 0, "type");

    // map pointer to type
    ContextImpl* meta             = module->getContext()->getMetadata();
    llvm::ExecutionEngine* engine = meta->getBackendEngine();
    engine->addGlobalMapping(m_backendPointer, owner);
}

// destructor
TypeImpl::~TypeImpl() {
    // delete m_fields;
    // delete m_methods;
    delete m_addressMap;
    delete m_virtualTable;
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
    }
}

bool TypeImpl::isBase(const TypePtr type) const {
    return std::find(m_bases.begin(), m_bases.end(), type) != m_bases.end();
}
