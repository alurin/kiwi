/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "TypeImpl.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include "kiwi/Support/Array.hpp"
#include "kiwi/Members.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
UnaryOperator::UnaryOperator(
    Member::UnaryOpcode opcode,
    TypePtr ownerType,
    TypePtr returnType
) : Callable(ownerType, returnType, makeVector(ownerType, 0)), Overridable<UnaryOperator>(true), m_opcode(opcode) {
    m_memberID = UnaryID;
    ownerType->getMetadata()->unary().insert(this);
}

// constructor
BinaryOperator::BinaryOperator(
    Member::BinaryOpcode opcode,
    TypePtr ownerType,
    TypePtr returnType,
    TypePtr operandType
) : Callable(ownerType, returnType, makeVector(ownerType, operandType, 0)), Overridable<BinaryOperator>(true), m_opcode(opcode) {
    m_memberID = BinaryID;
    ownerType->getMetadata()->binary().insert(this);
}

// constructor
MultiaryOperator::MultiaryOperator(
    Member::MultiaryOpcode opcode,
    TypePtr ownerType,
    TypePtr returnType,
    TypeVector args
) : Callable(ownerType, returnType, makeVector(ownerType, args)), Overridable<MultiaryOperator>(true), m_opcode(opcode) {
    m_memberID = MultiaryID;
    ownerType->getMetadata()->multiary().insert(this);
}

// constructor
Field::Field(TypePtr ownerType, Field* field)
: Member(ownerType), m_name(field->getName()), m_fieldType(field->getFieldType()), Overridable<Field>(false) {
    override(field);
}

// constructor
Field::Field(const Identifier& name, TypePtr ownerType, TypePtr fieldType)
: Member(ownerType), m_name(name), m_fieldType(fieldType), Overridable<Field>(true) {
    m_memberID = FieldID;
    ownerType->getMetadata()->fields().insert(this);
}

// constructor
Method::Method(const Identifier& name, TypePtr ownerType, TypePtr returnType, TypeVector types)
: Callable(ownerType, returnType, makeVector(ownerType, types)), Overridable<Method>(true), m_name(name) {
    m_memberID = MethodID;
    ownerType->getMetadata()->methods().insert(this);
}

// constructor
Method::Method(TypePtr ownerType, Method* method)
: Callable(ownerType, method), Overridable<Method>(false), m_name(method->getName()) {
    override(method);
}

CastOperator::CastOperator(TypePtr sourceType, TypePtr destType)
: Callable(sourceType, destType, makeVector(sourceType, 0)), Overridable<CastOperator>(true) {
    m_memberID = CastID;
}
