/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "Codegen/Builder.hpp"
#include "Lang/Driver.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Exception.hpp"
#include "kiwi/Support/Cast.hpp"
#include "llvm/Module.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

using namespace kiwi;

typedef int32_t (*ReturnMainPoint)();

ModuleImpl::ModuleImpl() : m_backendModule(0) {
}

Module::Module(const Identifier& name, ContextPtr context)
: m_name(name), m_context(context), m_metadata(new ModuleImpl()) {
    ContextImpl* meta = context->getMetadata();

    m_metadata->m_backendModule = new llvm::Module(name, meta->getBackendContext());
    if (llvm::ExecutionEngine* engine = meta->getBackendEngine()) {
        engine->addModule(m_metadata->m_backendModule);
    }
}

Module::~Module() {
    delete m_metadata;
}

ModulePtr Module::create(const Identifier& name, ContextPtr context) {
    ModulePtr module = ModulePtr(new Module(name, context));
    context->getMetadata()->registerModule(module);
    return module;
}

MethodPtr Module::getMainMethod() {
    return m_metadata->mainMethod;
}

bool Module::includeFile(const Path& filename) {
    ContextPtr context = getContext();
    ObjectPtr type = dyn_cast<ObjectType>(this->find("Script"));
    if (!type) {
        type = ObjectType::create(shared_from_this(), "Script");
    }
    lang::DriverRef driver(context, type);
    if (driver.parseFile(filename)) {
        if (!m_metadata->mainMethod && driver.getMainMethod()) {
            m_metadata->mainMethod = driver.getMainMethod();
        }
        return true;
    }
    return false;
}

// Build module
/// @todo Constant propagation pass not worked
void Module::build() {
    // llvm::FunctionPassManager funcManager(m_module);
    // llvm::PassManager moduleManager;

    // /// create startup function
    // Method* mainMethod = getMainMethod();
    // if (mainMethod) {
    //     FunctionBuilder builder(mainMethod);
    //     builder.createJITStartupPoint();
    // }

    // // Set up the optimizer pipeline.  Start with registering info about how the
    // // target lays out data structures.
    // funcManager.add(new llvm::TargetData(*m_engine->getTargetData()));

    // int8_t level = getContext()->getOptimizationLevel();

    // // First level optimizations
    // if (level > 0) {
    //     // Do simple "peephole" optimizations and bit-twiddling optzns.
    //     funcManager.add(llvm::createInstructionCombiningPass());
    //     // Provide basic AliasAnalysis support for GVN.
    //     funcManager.add(llvm::createBasicAliasAnalysisPass());
    // }

    // // Second level optimizations
    // if (level > 1) {
    //     // Reassociate expressions.
    //     funcManager.add(llvm::createReassociatePass());
    //     // Eliminate Common SubExpressions.
    //     funcManager.add(llvm::createGVNPass());
    //     // Simplify the control flow graph (deleting unreachable blocks, etc).
    //     funcManager.add(llvm::createCFGSimplificationPass());
    //     funcManager.add(llvm::createConstantPropagationPass());
    // }

    // // Third level optimizations
    // if (level > 2) {
    //     funcManager.add(llvm::createDeadCodeEliminationPass());
    //     funcManager.add(llvm::createDeadStoreEliminationPass());
    //     moduleManager.add(llvm::createGlobalOptimizerPass());
    //     moduleManager.add(llvm::createStripDeadPrototypesPass());
    //     moduleManager.add(llvm::createConstantMergePass());
    // }

    // /// run optimizations passes for all functions in module
    // funcManager.doInitialization();
    // for (llvm::Module::iterator func = m_module->begin(); func != m_module->end(); ++func) {
    //     funcManager.run(*func);
    // }
    // /// run module optimizations passes
    // moduleManager.run(*m_module);
}

// Dump module
void Module::dump() {
    getMetadata()->getBackendModule()->dump();
}

// Run module main function
int32_t Module::run() {
    // // JIT the function, returning a function pointer.
    // llvm::Function* mainFunc = m_module->getFunction("__start");
    // if (mainFunc) {
    //     void *pointFunc          = m_engine->getPointerToFunction(mainFunc);
    //     ReturnMainPoint main     = reinterpret_cast<ReturnMainPoint>(reinterpret_cast<intptr_t>(pointFunc));
    //     return main();
    // }

    // throw "Not found main function";
    return 0;
}

// register type with alias
void ModuleImpl::registerType(TypePtr type, const Identifier& name) {
    m_types.insert(type);
    throw Exception()
        << exception_message("Module::registerType not implemented");
}

/// create alias for type
void ModuleImpl::registerType(TypePtr type) {
    m_types.insert(type);
}


TypePtr Module::find(const Identifier& name) {
    throw Exception()
        << exception_message("Module::find(name) not implemented");
}
