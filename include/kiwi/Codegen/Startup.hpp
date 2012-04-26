/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_STARTUP_INTERNAL
#define KIWI_CODEGEN_STARTUP_INTERNAL

#include "kiwi/Codegen/Expression.hpp"

namespace kiwi {
    class Method;

namespace codegen {
    /// Emitter for standart operation with objects
    class StartupEmitter {
    public:
        StartupEmitter(Method* method);

        llvm::Function* emitJIT();

        llvm::Function* emitNative();

    protected:
        Method* m_method;
    };

}} // namespace kiwi::codegen

#endif
