/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_VIRTUALTABLE_INTERNAL
#define KIWI_SUPPORT_VIRTUALTABLE_INTERNAL

namespace llvm {
    class GlobalVariable;
}

namespace kiwi {
    class VirtualTable {
    public:
        /// returns LLVM variable for current virtual table
        llvm::GlobalVariable* getBackendVariable() const;
    protected:
    };
}

#endif
