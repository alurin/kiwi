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
#include "kiwi/ManagedStatic.hpp"
#include "kiwi/Module.hpp"
#include "kiwi-runtime/core.h"
#include <llvm/LLVMContext.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/PassManager.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/IPO.h"
#include <unicode/uclean.h>
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
    GC_INIT();                          // GC init
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
ContextImpl::ContextImpl()
: m_backendContext(new llvm::LLVMContext()), m_backendEngine(0) {

}

ContextImpl::~ContextImpl() {
    delete m_backendEngine;
    delete m_backendContext;
}

// Constructor
Context::Context()
: m_metadata(new ContextImpl()), m_optimizationLevel(1), m_debug(false) {
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
    // m_metadata->runtime
    ModulePtr runtime    = m_metadata->runtime = Module::create("system", shared_from_this());

    // create types
    m_metadata->boolTy   = BooleanType::create(runtime);
    m_metadata->int32Ty  = IntegerType::create(runtime, 32, false);
    m_metadata->voidTy   = VoidType::create(runtime);
    m_metadata->charTy   = CharType::create(runtime);
    m_metadata->stringTy = StringType::create(runtime);

    // init runtime type
    initRuntimeModule(m_metadata->runtime);

    // create execution engine
    llvm::Module* module = runtime->getMetadata()->getBackendModule();
    // @todo remove exception
    m_metadata->m_backendEngine = llvm::EngineBuilder(module).create();
}
