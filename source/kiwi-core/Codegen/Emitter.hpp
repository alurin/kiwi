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
    class Callable;

    /// Abstract emmiter for unary operators
    class MethodPolicy {
    public:
        /// type for vector of expressions
        typedef std::vector<ValueBuilder> ExpressionVector;

        /// virtual destructor
        virtual ~MethodPolicy();

        /// emit IR instruction
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values) =0;
    }; // class Emitter


    class CloneEmitter : public MethodPolicy {
    public:
        CloneEmitter(MethodPtr callable);

        /// emit IR instruction
        virtual ValueBuilder emit(BlockBuilder block, const ExpressionVector& values);
    protected:
        MethodWeak m_callable;
    };

} // namespace kiwi::codegen

#endif
