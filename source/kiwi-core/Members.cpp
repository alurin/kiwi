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
) : Callable(ownerType, returnType, makeVector(ownerType)), Overridable<UnaryOperator>(true), m_opcode(opcode) {
    m_memberID = UnaryID;
}

// constructor
BinaryOperator::BinaryOperator(
    Member::BinaryOpcode opcode,
    TypePtr ownerType,
    TypePtr returnType,
    TypePtr operandType
) : Callable(ownerType, returnType, makeVector(ownerType, operandType)), Overridable<BinaryOperator>(true), m_opcode(opcode) {
    m_memberID = BinaryID;
}

// constructor
MultiaryOperator::MultiaryOperator(
    Member::MultiaryOpcode opcode,
    TypePtr ownerType,
    TypePtr returnType,
    TypeVector args
) : Callable(ownerType, returnType, makeVector(ownerType, args)), Overridable<MultiaryOperator>(true), m_opcode(opcode) {
    m_memberID = MultiaryID;
}

// constructor
Field::Field(TypePtr ownerType, FieldPtr field)
: Member(ownerType), m_name(field->getName()), m_fieldType(field->getFieldType()), Overridable<Field>(false) {
    override(field);
}

// constructor
Field::Field(const Identifier& name, TypePtr ownerType, TypePtr fieldType)
: Member(ownerType), m_name(name), m_fieldType(fieldType), Overridable<Field>(true) {
    m_memberID = FieldID;
}

// constructor
Method::Method(const Identifier& name, TypePtr ownerType, TypePtr returnType, TypeVector types)
: Callable(ownerType, returnType, makeVector(ownerType, types)), Overridable<Method>(true), m_name(name) {
    m_memberID = MethodID;
}

// constructor
Method::Method(TypePtr ownerType, MethodPtr method)
: Callable(ownerType, method), Overridable<Method>(false), m_name(method->getName()) {
    override(method);
}

CastOperator::CastOperator(TypePtr sourceType, TypePtr destType)
: Callable(sourceType, destType, makeVector(sourceType)), Overridable<CastOperator>(true) {
    m_memberID = CastID;
}
