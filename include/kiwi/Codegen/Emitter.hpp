/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_EMITTER_INCLUDED
#define KIWI_CODEGEN_EMITTER_INCLUDED

#include <vector>

namespace kiwi {
    class BlockBuilder;
    class ValueBuilder;

namespace codegen {
    /// Abstract emmiter for unary operators
    class CallableEmitter {
    public:
        /// type for vector of expressions
        typedef std::vector<ValueBuilder> ExpressionVector;

        /// virtual destructor
        virtual ~CallableEmitter();

        /// emit IR instruction
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values) =0;
    }; // class Emitter

}} // namespace kiwi::codegen

#endif
