/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_STRING_INTERNAL
#define KIWI_CODEGEN_STRING_INTERNAL

#include "kiwi/types.hpp"
#include "kiwi/Codegen/Expression.hpp"

namespace kiwi {
    class StringType;
namespace codegen {
    /// Emitter for standart operation with objects
    class StringEmitter {
    public:
        /// constructor
        StringEmitter(StringType* stringTy);

        /// emit constant string
        ExpressionGen emit(const StatementGen& gen, const String& value);
    protected:
        StringType* m_stringTy;
    };

}} // namespace kiwi::codegen

#endif
