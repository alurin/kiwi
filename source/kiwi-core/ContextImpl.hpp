/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CONTEXTIMPL_INTERNAL
#define KIWI_CONTEXTIMPL_INTERNAL

#include "kiwi/config.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <vector>

namespace llvm {
    class LLVMContext;
    class ExecutionEngine;
    class FunctionPassManager;
    class PassManager;
    class TargetData;
}

namespace kiwi {
    /// Internal class for store information of runtime types
    class ContextImpl {
        friend class Context;
    public:
        /// runtime module
        ModulePtr runtime;

        /// 32-bit integer type
        IntegerPtr int32Ty;

        /// boolean type
        BooleanPtr boolTy;

        /// void type
        VoidPtr voidTy;

        /// character type
        CharPtr charTy;

        /// string type
        StringPtr stringTy;

        /// returns LLVM context
        llvm::LLVMContext& getBackendContext() const {
            return *m_backendContext;
        }

        /// returns LLVM execution engine
        llvm::ExecutionEngine* getBackendEngine() const {
            return m_backendEngine;
        }

        /// returns LLVM function pass manager
        llvm::FunctionPassManager* getBackendFunctionPassManager() const {
            return m_backendFunctionPassManager;
        }

        /// returns LLVM module pass manager
        llvm::PassManager* getBackendModulePassManager() const {
            return m_backendModulePassManager;
        }

        /// LLVM target data
        llvm::TargetData* getBackendTargetData() const {
            return m_backendTargetData;
        }

        /// Register module in context
        void registerModule(ModulePtr module) {
            m_modules.push_back(module);
        }
    private:
        /// list of modules
        std::vector<ModulePtr> m_modules;

        /// LLVM context
        llvm::LLVMContext* m_backendContext;

        /// LLVM execution engine
        llvm::ExecutionEngine* m_backendEngine;

        /// LLVM function pass manager
        llvm::FunctionPassManager* m_backendFunctionPassManager;

        /// LLVM module pass manager
        llvm::PassManager* m_backendModulePassManager;

        /// LLVM target data
        llvm::TargetData* m_backendTargetData;

        /// constructor
        ContextImpl();

        /// destructor
        ~ContextImpl();
    };
}

#endif
