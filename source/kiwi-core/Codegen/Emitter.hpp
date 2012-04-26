/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_EMITTER_INTERNAL
#define KIWI_CODEGEN_EMITTER_INTERNAL

#include "Builder.hpp"
#include <vector>

namespace kiwi {
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
