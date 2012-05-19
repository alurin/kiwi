/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "AddressMap.hpp"
#include "kiwi/Module.hpp"
#include "../ModuleImpl.hpp"
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalVariable.h>

using namespace kiwi;

AddressMap::AddressMap(Type* owner, ModulePtr module)
: MemberSet<Field>(owner), m_backendVariable(0) {
    /// Create stub for address map
    llvm::Module* backendModule = module->getMetadata()->getBackendModule();
    llvm::LLVMContext& context  = backendModule->getContext();
    llvm::Type* offsetType      = llvm::Type::getInt32Ty(context);
    llvm::Type* addressMapStub  = llvm::ArrayType::get(offsetType, 0);
    llvm::Type* addressMapType  = addressMapStub->getPointerTo();

    /// Store stub variable
    llvm::Constant* nullValue = llvm::Constant::getNullValue(addressMapType);
    m_backendVariable = new llvm::GlobalVariable(*backendModule, addressMapType, false, llvm::GlobalValue::PrivateLinkage, nullValue, "::_amap");
}

void AddressMap::update() {
    m_backendVariable->setName(m_owner->getName() + "::_amap");
}
