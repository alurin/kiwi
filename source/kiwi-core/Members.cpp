/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include "kiwi/Support/Array.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/assert.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

/// constructor
Callable::Callable(Type* ownerType, Type* returnType, TypeVector types)
: Member(ownerType), m_returnType(returnType), m_func(0), m_emitter(0) {
    makeArgumentsFromTypes(types);
    kiwi_assert(m_args.size() > 0, "Callable must have minimum one argument");
    kiwi_assert(m_args[0]->getType() == ownerType, "First argument for callable must be owner type");
}

/// constructor
Callable::Callable(Type* ownerType, Type* returnType, TypeVector types, codegen::CallableEmitter* emitter)
: Member(ownerType), m_returnType(returnType), m_func(0), m_emitter(emitter) {
    makeArgumentsFromTypes(types);
    kiwi_assert(m_args.size() > 0, "Callable must have minimum one argument");
    kiwi_assert(m_args[0]->getType() == ownerType, "First argument for callable must be owner type");
}

Callable::~Callable() {
    for (std::vector<Argument*>::const_iterator i = m_args.begin(); i != m_args.end(); ++i) {
        Argument* arg = *i;
        delete arg;
    }
    delete m_emitter;
}

// constructor
UnaryOperator::UnaryOperator(
    Member::UnaryOpcode opcode,
    Type* ownerType,
    Type* returnType,
    codegen::CallableEmitter* emitter
) : Callable(ownerType, returnType, makeVector(ownerType, 0), emitter), m_opcode(opcode) {
    m_memberID = UnaryID;
}

// constructor
BinaryOperator::BinaryOperator(
    Member::BinaryOpcode opcode,
    Type* ownerType,
    Type* returnType,
    Type* operandType,
    codegen::CallableEmitter* emitter
) : Callable(ownerType, returnType, makeVector(ownerType, operandType, 0), emitter), m_opcode(opcode) {
    m_memberID = BinaryID;
}

// constructor
MultiaryOperator::MultiaryOperator(
    Member::MultiaryOpcode opcode,
    Type* ownerType,
    Type* returnType,
    TypeVector args,
    codegen::CallableEmitter* emitter
) : Callable(ownerType, returnType, makeVector(ownerType, args), emitter), m_opcode(opcode) {
    m_memberID = MultiaryID;
}

// constructor
Field::Field(const Identifier& name, Type* ownerType, Type* fieldType)
: Member(ownerType), m_name(name), m_fieldType(fieldType) {
    m_memberID = FieldID;
}

// constructor
Method::Method(const Identifier& name, Type* ownerType, Type* returnType, TypeVector types)
: Callable(ownerType, returnType, makeVector(ownerType, types)), m_name(name) {
    m_memberID = MethodID;
}

// constructor
Argument::Argument(Callable* owner, Type* type, int32_t position)
: m_owner(owner), m_type(type) { }

CastOperator::CastOperator(Type* sourceType, Type* destType)
: Callable(sourceType, destType, makeVector(sourceType, 0)) {
    m_memberID = CastID;
}

/// Check signature
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
    if (!m_emitter) {
        m_emitter = new codegen::LlvmCallEmitter(func, m_returnType);
    }
}

void Callable::makeArgumentsFromTypes(TypeVector types) {
    for (TypeVector::iterator i = types.begin(); i != types.end(); ++i) {
        Type* type = *i;
        Argument* arg = new Argument(this, type, m_args.size());
        m_args.push_back(arg);
    }
}
