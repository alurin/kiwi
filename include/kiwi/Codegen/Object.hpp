/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CODEGEN_OBJECT_INTERNAL
#define KIWI_CODEGEN_OBJECT_INTERNAL

#include "kiwi/types.hpp"
#include "kiwi/Codegen/Expression.hpp"

namespace kiwi {
    class ObjectType;

namespace codegen {
    /// Emitter for standart operation with objects
    class ObjectEmitter {
    public:
        ObjectEmitter(ObjectType* type);

        /// emit instructions for load value from object field
        ExpressionGen emitLoad(const StatementGen& gen, const ExpressionGen& thisValue, const Identifier& name);

        /// emit instructions for store value in object field
        ExpressionGen emitStore(const StatementGen& gen, const ExpressionGen& thisValue, const Identifier& name, const ExpressionGen& value);

        /// emit instruction for create new instance of class
        ExpressionGen emitNew(const StatementGen& gen);
    protected:
        ObjectType* m_type;

        /// Returns pointer to value of field obkect
        ExpressionGen findField(const StatementGen& gen, const ExpressionGen& thisValue, const Identifier& name);

        /// Returns pointer to method of object
        ExpressionGen findMethod(const StatementGen& gen, const ExpressionGen& thisValue, const Identifier& name);
    };

}} // namespace kiwi::codegen

#endif
