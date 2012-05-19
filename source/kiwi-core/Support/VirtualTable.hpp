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

        /// update virtual table
        void update();

        /// return pointer for virtual table
        void* getPointer() {
            return 0;
        }

        /// return next position from virtual table
        int32_t nextPosition();
    protected:
        /// global variable for store pointer to vtable
        llvm::GlobalVariable* m_backendVariable;

        /// size of last vtable
        int32_t m_lastSize;

        /// last position
        int32_t m_lastPosition;
    };
}

#endif
