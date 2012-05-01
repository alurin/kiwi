/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Emitter.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

CallablePolicy::~CallablePolicy() {
}

CloneEmitter::CloneEmitter(CallablePolicy* emitter)
: m_emitter(emitter) {
}

/// emit IR instruction
ValueBuilder CloneEmitter::emit(BlockBuilder block, const ExpressionVector& values) {
    return m_emitter->emit(block, values);
}
