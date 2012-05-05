/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Emitter.hpp"
#include "kiwi/Callable.hpp"
#include "kiwi/Exception.hpp"

using namespace kiwi;

CallablePolicy::~CallablePolicy() {
}

CloneEmitter::CloneEmitter(CallablePtr callable)
: m_callable(callable) {
}

/// emit IR instruction
ValueBuilder CloneEmitter::emit(BlockBuilder block, const ExpressionVector& values) {
    CallablePolicy* policy = m_callable.lock()->getPolicy();
    if (policy) {
        return policy->emit(block, values);
    } else {
        throw Exception()
            << exception_message("Policy not found for function");
    }
}
