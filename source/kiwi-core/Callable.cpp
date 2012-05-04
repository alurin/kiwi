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
Callable::Callable(TypePtr ownerType, TypePtr returnType, TypeVector types)
: Member(ownerType), m_returnType(returnType), m_func(0), m_policy(0) {
    makeArgumentsFromTypes(types);
    kiwi_assert(m_args.size() > 0, "Callable must have minimum one argument");
    kiwi_assert(m_args[0]->getType() == ownerType, "First argument for callable must be owner type");
}

// constructor
Callable::Callable(TypePtr ownerType, Callable* callable)
: Member(ownerType), m_returnType(callable->m_returnType), m_func(0), m_policy(new CloneEmitter(callable)) {
    cloneArguments(ownerType, callable->m_args);
    kiwi_assert(m_args.size() > 0, "Callable must have minimum one argument");
    kiwi_assert(m_args[0]->getType() == ownerType, "First argument for callable must be owner type");

}

Callable::~Callable() {
    for (std::vector<Argument*>::const_iterator i = m_args.begin(); i != m_args.end(); ++i) {
        Argument* arg = *i;
        delete arg;
    }
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
        setPolicy(new LlvmCallEmitter(func, m_returnType));
    }
}

void Callable::makeArgumentsFromTypes(TypeVector types) {
    for (TypeVector::iterator i = types.begin(); i != types.end(); ++i) {
        TypePtr type = *i;
        Argument* arg = new Argument(this, type, m_args.size());
        m_args.push_back(arg);
    }
}

void Callable::cloneArguments(TypePtr thisType, ArgumentVector args) {
    int j = 0;
    for (ArgumentVector::iterator i = args.begin(); i != args.end(); ++i, ++j) {
        if (j) {
            Argument* oarg = *i;
            Argument* arg = new Argument(*oarg);
            m_args.push_back(arg);
        } else {
            Argument* arg = new Argument(this, thisType, 0);
            m_args.push_back(arg);
        }
    }
}
