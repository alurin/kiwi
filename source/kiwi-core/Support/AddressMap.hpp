/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_SUPPORT_ADDRESSMAP_INTERNAL
#define KIWI_SUPPORT_ADDRESSMAP_INTERNAL

#include "MemberSet.hpp"

namespace llvm {
    class GlobalVariable;
}

namespace kiwi {
    class AddressMap : public MemberSet<Field> {
    public:
        /// constructor
        AddressMap(Type* owner, ModulePtr module);

        /// returns LLVM variable for current address map
        llvm::GlobalVariable* getBackendVariable() const {
            return m_backendVariable;
        }

        /// return pointer for address map
        void* getPointer() {
            return 0;
        }
    protected:
        llvm::GlobalVariable* m_backendVariable;
    };
}

#endif
