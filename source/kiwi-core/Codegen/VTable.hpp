/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_VTABLE_INTERNAL
#define KIWI_CODEGEN_VTABLE_INTERNAL

#include "llvm/GlobalVariable.h"

namespace kiwi {
namespace codegen {
    /// Emitter for address maps
    class StructEmitter {
    public:
        /// Add field in ptr and returns index of this field
        uint32_t add(FieldPtr field);

    protected:
        /// Global varible for store pointer to amap
        GlobalVariable* amap;

        std::vector<int32_t> field;
    };

}}

#endif
