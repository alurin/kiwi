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

using namespace kiwi;

AddressMap::AddressMap(ModulePtr module)
: m_backendVariable(0) {
    // llvm::Module* backendModule = module->getMetadata()->getBackendModule();

    // m_type
    // m_backendVariable
}
