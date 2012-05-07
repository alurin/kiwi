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
#include <llvm/PassManager.h>
#include <llvm/LLVMContext.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
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
: m_backendContext(new llvm::LLVMContext()), m_backendEngine(0)
, m_backendFunctionPassManager(0), m_backendModulePassManager(0) {
}

ContextImpl::~ContextImpl() {
    delete m_backendFunctionPassManager;
    delete m_backendModulePassManager;
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
    ModulePtr runtime    = m_metadata->runtime = Module::create("system", shared_from_this());

    // create execution engine
    llvm::Module* module                    = runtime->getMetadata()->getBackendModule();
    m_metadata->m_backendEngine             = llvm::EngineBuilder(module).create();
    m_metadata->m_backendTargetData         = new llvm::TargetData(*m_metadata->m_backendEngine->getTargetData());

    // Set up the optimizer pipeline.
    llvm::FunctionPassManager* funcManager  = new llvm::FunctionPassManager(module);
    llvm::PassManager* moduleManager        = new llvm::PassManager();

    // Start with registering info about how the target lays out data structures.
    funcManager->add(m_metadata->m_backendTargetData);

    // First level optimizations
    switch (getOptimizationLevel()) {
        case 3:
            moduleManager->add(llvm::createGlobalOptimizerPass());
            moduleManager->add(llvm::createStripDeadPrototypesPass());
        case 2:
            funcManager->add(llvm::createDeadCodeEliminationPass());
            funcManager->add(llvm::createDeadStoreEliminationPass());

        case 1:
            // Provide basic AliasAnalysis support for GVN.
            funcManager->add(llvm::createBasicAliasAnalysisPass());
            // Promote allocas to registers.
            funcManager->add(llvm::createPromoteMemoryToRegisterPass());
            // Do simple "peephole" optimizations and bit-twiddling optzns.
            funcManager->add(llvm::createInstructionCombiningPass());
            // Reassociate expressions.
            funcManager->add(llvm::createReassociatePass());
            // Eliminate Common SubExpressions.
            funcManager->add(llvm::createGVNPass());
            // Simplify the control flow graph (deleting unreachable blocks, etc).
            funcManager->add(llvm::createCFGSimplificationPass());
            // Merge constants, e.g. strings
            moduleManager->add(llvm::createConstantMergePass());
        default:
            break;
    }
    /// run optimizations passes for all functions in module
    funcManager->doInitialization();

    m_metadata->m_backendFunctionPassManager = funcManager;
    m_metadata->m_backendModulePassManager   = moduleManager;

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

    throw Exception()
        << exception_format("Not found `main` function in module `%1%`", module->getName());
}
