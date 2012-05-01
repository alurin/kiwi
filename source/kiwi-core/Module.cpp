/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "Codegen/Builder.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Cast.hpp"
#include "Lang/Driver.hpp"
#include "llvm/Analysis/Passes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/IPO.h"

using namespace kiwi;

typedef int32_t (*ReturnMainPoint)();

Module::Module(const Identifier& name, Context* context)
: m_name(name), m_context(context), m_module(0), m_engine(0), m_metadata(new ModuleImpl()) {
    m_context->getMetadata()->modules.push_back(this);
    m_module = new llvm::Module(name, context->getContext());
    m_engine = llvm::EngineBuilder(m_module).create();

    if (name != Identifier("system")) {
        m_module->addLibrary("system");
    }
}

Module::~Module() {
    for (std::vector<Type*>::iterator i = m_metadata->types.begin(); i != m_metadata->types.end(); ++i) {
        Type* type = *i;
        delete type;
    }
    delete m_metadata;
    delete m_engine;
    // delete m_module;
}

Module* Module::create(const Identifier& name, Context* ref) {
    Module* module = new Module(name, ref);
    return module;
}

Method* Module::getMainMethod() {
    return m_metadata->mainMethod;
}

bool Module::includeFile(const Path& filename) {
    Context* context = getContext();
    ObjectType* type = dyn_cast<ObjectType>(this->find("Script"));
    if (!type) {
        type = ObjectType::create(this, "Script");
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
    llvm::FunctionPassManager funcManager(m_module);
    llvm::PassManager moduleManager;

    /// create startup function
    Method* mainMethod = getMainMethod();
    if (mainMethod) {
        FunctionBuilder builder(mainMethod);
        builder.createJITStartupPoint();
    }

    // Set up the optimizer pipeline.  Start with registering info about how the
    // target lays out data structures.
    funcManager.add(new llvm::TargetData(*m_engine->getTargetData()));

    int8_t level = getContext()->getOptimizationLevel();

    // First level optimizations
    if (level > 0) {
        // Do simple "peephole" optimizations and bit-twiddling optzns.
        funcManager.add(llvm::createInstructionCombiningPass());
        // Provide basic AliasAnalysis support for GVN.
        funcManager.add(llvm::createBasicAliasAnalysisPass());
    }

    // Second level optimizations
    if (level > 1) {
        // Reassociate expressions.
        funcManager.add(llvm::createReassociatePass());
        // Eliminate Common SubExpressions.
        funcManager.add(llvm::createGVNPass());
        // Simplify the control flow graph (deleting unreachable blocks, etc).
        funcManager.add(llvm::createCFGSimplificationPass());
        funcManager.add(llvm::createConstantPropagationPass());
    }

    // Third level optimizations
    if (level > 2) {
        funcManager.add(llvm::createDeadCodeEliminationPass());
        funcManager.add(llvm::createDeadStoreEliminationPass());
        moduleManager.add(llvm::createGlobalOptimizerPass());
        moduleManager.add(llvm::createStripDeadPrototypesPass());
        moduleManager.add(llvm::createConstantMergePass());
    }

    /// run optimizations passes for all functions in module
    funcManager.doInitialization();
    for (llvm::Module::iterator func = m_module->begin(); func != m_module->end(); ++func) {
        funcManager.run(*func);
    }
    /// run module optimizations passes
    moduleManager.run(*m_module);
}

// Dump module
void Module::dump() {
    m_module->dump();
}

// Run module main function
int32_t Module::run() {
    // JIT the function, returning a function pointer.
    llvm::Function* mainFunc = m_module->getFunction("__start");
    if (mainFunc) {
        void *pointFunc          = m_engine->getPointerToFunction(mainFunc);
        ReturnMainPoint main     = reinterpret_cast<ReturnMainPoint>(reinterpret_cast<intptr_t>(pointFunc));
        return main();
    }

    throw "Not found main function";
}

// register type with alias
void Module::registerType(Type* type, const Identifier& name) {
    if (type->getModule() == this && this->find(name) == 0) {
        m_names.insert(std::make_pair(name, type));
    }
}

Type* Module::find(const Identifier& name) {
    std::map<Identifier, Type*>::iterator result = m_names.find(name);
    if (result != m_names.end()) {
        return result->second;
    }
    return 0;
}
