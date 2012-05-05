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
        llvm::LLVMContext& getBackendContext() {
            return *m_backendContext;
        }

        /// returns LLVM execution engine
        llvm::ExecutionEngine* getBackendEngine() {
            return m_backendEngine;
        }

        /// Register module in context
        void registerModule(ModulePtr module) {
            m_modules.push_back(module);
        }
    private:
        /// LLVM context
        llvm::LLVMContext* m_backendContext;

        /// LLVM execution engine
        llvm::ExecutionEngine* m_backendEngine;

        /// list of modules
        std::vector<ModulePtr> m_modules;

        /// constructor
        ContextImpl();

        /// destructor
        ~ContextImpl();
    };
}

#endif
