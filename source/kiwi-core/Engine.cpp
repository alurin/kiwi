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

    kiwi_dummy();                       // Init kiwi-runtime (link as dummy)
    GC_INIT();                          // GC init
    u_init(&errorCode);                 // ICU init
    // llvm_start_multithreaded();      // LLVM init as multithreaded
    llvm::InitializeNativeTarget();     // LLVM JIT init
}

// shut down runtime
void kiwi::shutdown() {
    llvm::llvm_shutdown();              // LLVM cleanup
    u_cleanup();                        // ICU cleanup
    GC_gcollect();                      // GC cleanup
}
