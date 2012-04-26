/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_FUNCTION_INCLUDED
#define KIWI_CODEGEN_FUNCTION_INCLUDED

#include <vector>

namespace llvm {
    class Function;
    class FunctionType;
}

namespace kiwi {
    class Method;

    /// Emitter for method calls and definitions
    class MethodEmitter {
    public:
        /// constructor
        MethodEmitter(Method* method);

        /// emit method type
        llvm::FunctionType* emitType();

        /// emit method definition
        llvm::Function* emitDefinition();
    protected:
        Method* m_method;
    };

}

#endif
