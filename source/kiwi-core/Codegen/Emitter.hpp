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

    /// Abstract converter from this type to concrete type and vice versa
    class ThisConverter {
    public:
        /// Convert from variable to this
        virtual ValueBuilder emitToThis(BlockBuilder block, ValueBuilder variableValue) =0;

        /// Convert from this to variable
        virtual ValueBuilder emitFromThis(BlockBuilder block, ValueBuilder thisValue) =0;
    };

} // namespace kiwi::codegen

#endif
