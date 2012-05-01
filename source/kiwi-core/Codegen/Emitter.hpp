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
    /// Abstract emmiter for unary operators
    class CallablePolicy {
    public:
        /// type for vector of expressions
        typedef std::vector<ValueBuilder> ExpressionVector;

        /// virtual destructor
        virtual ~CallablePolicy();

        /// emit IR instruction
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values) =0;
    }; // class Emitter

namespace codegen {
    class CloneEmitter : public CallablePolicy {
    public:
        CloneEmitter(CallablePolicy* emitter);

        /// emit IR instruction
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        CallablePolicy* m_emitter;
    };

}} // namespace kiwi::codegen

#endif
