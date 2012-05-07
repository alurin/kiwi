/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_VIRTUALTABLE_INTERNAL
#define KIWI_SUPPORT_VIRTUALTABLE_INTERNAL

#include "MemberSet.hpp"

namespace llvm {
    class Type;
    class GlobalVariable;
}

namespace kiwi {
    class VirtualTable : public MemberSet<Method> {
    public:
        /// Constructor
        VirtualTable(Type* owner, ModulePtr module);

        /// returns LLVM variable for current virtual table
        llvm::GlobalVariable* getBackendVariable() const {
            return m_backendVariable;
        }

        /// return pointer for virtual table
        void* getPointer() {
            return 0;
        }
    protected:
        llvm::GlobalVariable* m_backendVariable;
    };
}

#endif
