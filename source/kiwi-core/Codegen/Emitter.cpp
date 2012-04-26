/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Codegen/Emitter.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

CallableEmitter::~CallableEmitter() {
}

ExpressionGen UnaryEmitter::emit(const StatementGen& gen, const ExpressionVector& values) {
    if (values.size() != 1) {
        throw "Expressions for emitter must containts only one elements";
    }
    return emit(gen, values[0]);
}

ExpressionGen BinaryEmitter::emit(const StatementGen& gen, const ExpressionVector& values) {
    if (values.size() != 2) {
        throw "Expressions for emitter must containts only two elements";
    }
    return emit(gen, values[0], values[1]);
}
