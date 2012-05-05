/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Callable.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Argument.hpp"
#include "Codegen/Emitter.hpp"
#include "Codegen/LlvmEmitter.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
Callable::Callable(TypePtr ownerType, TypePtr returnType)
: Member(ownerType), m_returnType(returnType), m_func(0), m_policy(0) {
}

// constructor
Callable::Callable(TypePtr ownerType, CallablePtr callable)
: Member(ownerType), m_returnType(callable->m_returnType), m_func(0), m_policy(new CloneEmitter(callable)) {
}

Callable::~Callable() {
    delete m_policy;
}

// Check signature
bool Callable::hasSignature(const TypeVector& types, bool isCast) const {
    if (types.size() != m_args.size())
        return false;

    for (int i = 0; i < m_args.size(); ++i) {
        /// @todo Replace for simple check
        if (m_args[i]->getType() != types[i])
            if (!types[i]->isCastableTo(m_args[i]->getType()))
                return false;
    }

    return true;
}

void Callable::setFunction(llvm::Function* func) {
    m_func = func;
    /// @todo What if, policy already exists at this point?
    if (!getPolicy()) {
        setPolicy(new LlvmCallEmitter(func, m_returnType.lock()));
    }
}

void Callable::initializateArguments(TypeVector types) {
    for (TypeVector::iterator i = types.begin(); i != types.end(); ++i) {
        TypePtr type = *i;
        ArgumentPtr arg = ArgumentPtr(new Argument(CallablePtr(shared_from_this(), this), type, m_args.size()));
        m_args.push_back(arg);
    }
    kiwi_assert(m_args.size() > 0, "Callable must have minimum one argument");
    kiwi_assert(m_args[0]->getType() == m_ownerType.lock(), "First argument for callable must be owner type");
}

void Callable::initializateArguments(TypePtr thisType, ArgumentVector args) {
    int j = 0;
    for (ArgumentVector::iterator i = args.begin(); i != args.end(); ++i, ++j) {
        if (j) {
            ArgumentPtr oarg = *i;
            ArgumentPtr arg = ArgumentPtr(new Argument(*oarg));
            m_args.push_back(arg);
        } else {
            ArgumentPtr arg = ArgumentPtr(new Argument(CallablePtr(shared_from_this(), this), thisType, 0));
            m_args.push_back(arg);
        }
    }
    kiwi_assert(m_args.size() > 0, "Callable must have minimum one argument");
    kiwi_assert(m_args[0]->getType() == m_ownerType.lock(), "First argument for callable must be owner type");
}
