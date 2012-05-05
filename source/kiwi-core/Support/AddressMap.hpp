/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_ADDRESSMAP_INTERNAL
#define KIWI_SUPPORT_ADDRESSMAP_INTERNAL

#include "kiwi/types.hpp"

namespace llvm {
    class GlobalVariable;
}

namespace kiwi {
    class AddressMap {
    public:
        /// constructor
        AddressMap(ModulePtr module);

        /// returns LLVM variable for current address map
        llvm::GlobalVariable* getBackendVariable() const {
            return m_backendVariable;
        }
    protected:
        llvm::GlobalVariable* m_backendVariable;
    };
}

#endif
