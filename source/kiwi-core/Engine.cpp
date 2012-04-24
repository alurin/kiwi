#include "kiwi/Engine.hpp"
#include "kiwi-runtime/core.h"
#include <llvm/LLVMContext.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <unicode/uclean.h>
#include "kiwi-runtime/gc.h"
#include "gc.h"

// start up runtime
void kiwi::startup() {
    UErrorCode errorCode;

    kiwi_dummy();                       // Include kiwi-runtime dummy
    GC_INIT();                          // GC
    u_init(&errorCode);                 // ICU
    // llvm_start_multithreaded();      // LLVM as multithreaded
    llvm::InitializeNativeTarget();     // LLVM JIT
}

// shut down runtime
void kiwi::shutdown() {
    llvm::llvm_shutdown();              // LLVM
    u_cleanup();                        // ICU
    GC_gcollect();                      // GC
}
