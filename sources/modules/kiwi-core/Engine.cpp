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
Engine::Engine() {

}

// Destruct engine 
Engine::~Engine() {
}

namespace kiwi {
    // Startup Kiwi and related libraries
    void startup() {
        UErrorCode errorCode;
        u_init(&errorCode);                 // ICU
        llvm::InitializeNativeTarget();     // LLVM JIT
    }

    // Shutdown Kiwi and related libraries
    void shutdown() {
        llvm::llvm_shutdown();              // LLVM 
        u_cleanup();                        // ICU
    }
}