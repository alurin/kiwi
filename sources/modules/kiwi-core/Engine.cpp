/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#include "kiwi/Engine.hpp"
#include <llvm/Support/TargetSelect.h>
#include <llvm/LLVMContext.h>
#include <llvm/Support/ManagedStatic.h>
#include <unicode/uclean.h>

using namespace kiwi;

// Create engine
Engine::Engine(Host* host) : m_host(host) {
    kiwi_assert(host && "Host must not be is null");
}

// Destruct engine
Engine::~Engine() {
}

// Startup Kiwi and related libraries
GlobalConfiguration::GlobalConfiguration() {
    UErrorCode errorCode;
    u_init(&errorCode);                 // ICU
    llvm::InitializeNativeTarget();     // LLVM JIT
}

// Clean up Kiwi and related libraries
GlobalConfiguration::~GlobalConfiguration() {
    llvm::llvm_shutdown();              // LLVM
    u_cleanup();                        // ICU
}
