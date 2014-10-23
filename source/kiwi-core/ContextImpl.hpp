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
#include <llvm/IR/PassManager.h>

namespace llvm {
    class LLVMContext;
    class ExecutionEngine;
    class FunctionPassManager;
    class ModulePassManager;
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
        llvm::FunctionPassManager* getBackendFunctionPassManager() const;

        /// returns LLVM module pass manager
        llvm::ModulePassManager* getBackendModulePassManager() const;

        /// Register module in context
        void registerModule(ModulePtr module) {
            m_modules.push_back(module);
        }
    private:
        /// Owner context
        Context* m_owner;

        /// list of modules
        std::vector<ModulePtr> m_modules;

        /// LLVM context
        llvm::LLVMContext* m_backendContext;

        /// LLVM execution engine
        llvm::ExecutionEngine* m_backendEngine;

        /// LLVM function pass manager
        mutable llvm::FunctionPassManager* m_backendFunctionPassManager;

        /// LLVM module pass manager
        mutable llvm::ModulePassManager* m_backendModulePassManager;

        /// constructor
        ContextImpl(Context* context);

        /// destructor
        ~ContextImpl();

        /// init pass managers and target data
        void initPassManagers() const;
    };
}

#endif
