/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include <llvm/PassManager.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Target/TargetData.h>

using namespace kiwi;

// constructor
ContextImpl::ContextImpl(Context* context)
: m_backendContext(new llvm::LLVMContext()), m_backendEngine(0)
, m_backendFunctionPassManager(0), m_backendModulePassManager(0)
, m_backendTargetData(0), m_owner(context) {
}

// destructor
ContextImpl::~ContextImpl() {
    delete m_backendFunctionPassManager;
    delete m_backendModulePassManager;
    delete m_backendEngine;
    delete m_backendContext;
}

/// returns LLVM function pass manager
llvm::FunctionPassManager* ContextImpl::getBackendFunctionPassManager() const {
    if (!m_backendFunctionPassManager)  {
        initPassManagers();
    }
    return m_backendFunctionPassManager;
}

// Set up the optimizer pipeline.
llvm::PassManager* ContextImpl::getBackendModulePassManager() const {
    if (!m_backendModulePassManager)  {
        initPassManagers();
    }
    return m_backendModulePassManager;
}

void ContextImpl::initPassManagers() const {
    // Set up the optimizer pipeline.
    llvm::Module* module = runtime->getMetadata()->getBackendModule();
    llvm::FunctionPassManager* m_funcManager  = new llvm::FunctionPassManager(module);
    llvm::PassManager* m_moduleManager        = new llvm::PassManager();

    // Start with registering info about how the target lays out data structures.
    m_funcManager->add(const_cast<llvm::TargetData*>(m_backendTargetData));

#ifdef KIWI_DEBUG
    m_funcManager->add(llvm::createInstructionNamerPass());
#endif

    // First level optimizations
    {
        int8_t level = m_owner->getOptimizationLevel();
        if (level >= 1) {
            // Provide basic AliasAnalysis support for GVN.
            m_funcManager->add(llvm::createBasicAliasAnalysisPass());
            // Promote allocas to registers.
            m_funcManager->add(llvm::createPromoteMemoryToRegisterPass());
            // Do simple "peephole" optimizations and bit-twiddling optzns.
            m_funcManager->add(llvm::createInstructionCombiningPass());
            // Reassociate expressions.
            m_funcManager->add(llvm::createReassociatePass());
            // Eliminate Common SubExpressions.
            m_funcManager->add(llvm::createGVNPass());
            // Simplify the control flow graph (deleting unreachable blocks, etc).
            m_funcManager->add(llvm::createCFGSimplificationPass());
            // Merge constants, e.g. strings
            m_moduleManager->add(llvm::createConstantMergePass());
        }
        if (level >= 2) {
            m_funcManager->add(llvm::createDeadCodeEliminationPass());

            m_funcManager->add(llvm::createDeadStoreEliminationPass());
        }
        if (level >= 3) {
            m_moduleManager->add(llvm::createGlobalOptimizerPass());

            m_moduleManager->add(llvm::createStripDeadPrototypesPass());

            m_funcManager->add(llvm::createTailCallEliminationPass());
        }
    }
    /// run optimizations passes for all functions in module
    m_funcManager->doInitialization();

    /// store pass managers
    m_backendModulePassManager = m_moduleManager;
    m_backendFunctionPassManager = m_funcManager;
}
