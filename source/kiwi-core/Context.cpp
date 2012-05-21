/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "RuntimeModule.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/ManagedStatic.hpp"
#include "kiwi/Module.hpp"
#include "kiwi-runtime/core.h"
#include <unicode/uclean.h>
#include <llvm/Module.h>
#include <llvm/LLVMContext.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#ifdef KIWI_GC
    #include "gc.h"
#endif

using namespace kiwi;

// Initialize resources for vendor libraries
void kiwi::startup() {
    UErrorCode errorCode;

    kiwi_dummy();                       // Init kiwi-runtime (link as dummy)
    u_init(&errorCode);                 // ICU init
    llvm::llvm_start_multithreaded();   // LLVM init as multithreaded
    llvm::InitializeNativeTarget();     // LLVM JIT init

    #ifdef KIWI_GC
    GC_enable_incremental();            // GC init
    #endif
}

// Clean up resource for vendor libraries
void kiwi::shutdown() {
    llvm::llvm_shutdown();              // LLVM cleanup
    u_cleanup();                        // ICU cleanup

    #ifdef KIWI_GC
    GC_gcollect();                      // GC cleanup
    #endif
}

// Constructor
Context::Context()
: m_metadata(new ContextImpl(this)), m_optimizationLevel(1), m_debug(false) {
}

Context::~Context() {
    delete m_metadata;
}

ContextPtr Context::create() {
    ContextPtr context = ContextPtr(new Context());
    context->initializate();
    return context;
}

void Context::initializate() {
    // create system module
    ModulePtr runtime = m_metadata->runtime = Module::create("system", shared_from_this());

    // create execution engine
    llvm::Module* module            = runtime->getMetadata()->getBackendModule();
    m_metadata->m_backendEngine     = llvm::EngineBuilder(module).create();
    m_metadata->m_backendTargetData = new llvm::TargetData(*m_metadata->m_backendEngine->getTargetData());

    // create types
    m_metadata->boolTy   = BooleanType::create(runtime);
    m_metadata->int32Ty  = IntegerType::create(runtime, 32, false);
    m_metadata->voidTy   = VoidType::create(runtime);
    m_metadata->charTy   = CharType::create(runtime);
    m_metadata->stringTy = StringType::create(runtime);

    // init runtime type
    initRuntimeModule(m_metadata->runtime);
}

int32_t Context::run(ModulePtr module) {
    typedef int32_t (*ReturnMainPoint)();

    // JIT the function, returning a function pointer.
    module->build();
    llvm::Module* backendModule = module->getMetadata()->getBackendModule();
    llvm::Function* mainFunc    = backendModule->getFunction("__start");
    if (mainFunc) {
        void *pointFunc         = m_metadata->getBackendEngine()->getPointerToFunction(mainFunc);
        ReturnMainPoint main    = reinterpret_cast<ReturnMainPoint>(reinterpret_cast<intptr_t>(pointFunc));
        return main();
    }

    BOOST_THROW_EXCEPTION(Exception()
        << exception_format("Not found `main` function in module `%1%`", module->getName()));
}
