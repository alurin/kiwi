/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Emitter.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Exception.hpp"

using namespace kiwi;

MethodPolicy::~MethodPolicy() {
}

CloneEmitter::CloneEmitter(MethodPtr callable)
: m_callable(callable) {
}

/// emit IR instruction
ValueBuilder CloneEmitter::emit(BlockBuilder block, const ExpressionVector& values) {
    MethodPolicy* policy = m_callable.lock()->getPolicy();
    if (policy) {
        return policy->emit(block, values);
    } else {
        throw Exception()
            << exception_message("Policy not found for function");
    }
}
