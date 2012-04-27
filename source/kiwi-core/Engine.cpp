/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Engine.hpp"
#include "kiwi-runtime/core.h"
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <unicode/uclean.h>
#ifdef KIWI_GC
    #include "gc.h"
#endif

// start up runtime
void kiwi::startup() {
    UErrorCode errorCode;

    kiwi_dummy();                       // Init kiwi-runtime (link as dummy)
    u_init(&errorCode);                 // ICU init
    // llvm_start_multithreaded();      // LLVM init as multithreaded
    llvm::InitializeNativeTarget();     // LLVM JIT init

#ifdef KIWI_GC
    GC_INIT();                          // GC init
#endif
}

// shut down runtime
void kiwi::shutdown() {
    llvm::llvm_shutdown();              // LLVM cleanup
    u_cleanup();                        // ICU cleanup

#ifdef KIWI_GC
    GC_gcollect();                      // GC cleanup
#endif
}
