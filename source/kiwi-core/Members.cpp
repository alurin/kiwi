/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "TypeImpl.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Type.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
UnaryOperator::UnaryOperator(Member::UnaryOpcode opcode, TypePtr ownerType, TypePtr returnType)
: Callable(ownerType, returnType), Overridable<UnaryOperator>(true), m_opcode(opcode) {
    m_memberID = UnaryID;
}

// constructor
BinaryOperator::BinaryOperator(Member::BinaryOpcode opcode, TypePtr ownerType, TypePtr returnType)
: Callable(ownerType, returnType), Overridable<BinaryOperator>(true), m_opcode(opcode) {
    m_memberID = BinaryID;
}

// constructor
MultiaryOperator::MultiaryOperator(Member::MultiaryOpcode opcode, TypePtr ownerType, TypePtr returnType)
: Callable(ownerType, returnType), Overridable<MultiaryOperator>(true), m_opcode(opcode) {
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
Method::Method(const Identifier& name, TypePtr ownerType, TypePtr returnType)
: Callable(ownerType, returnType), Overridable<Method>(true), m_name(name) {
    m_memberID = MethodID;
}

// constructor
Method::Method(TypePtr ownerType, MethodPtr method)
: Callable(ownerType, method), Overridable<Method>(false), m_name(method->getName()) {
    override(method);
}

// Create method add register in type
MethodPtr Method::create(TypePtr ownerType, TypePtr returnType, std::vector<TypePtr> types, const Identifier& name) {
    MethodPtr method = MethodPtr(new Method(name, ownerType, returnType));
    ownerType->getMetadata()->methods().insert(method);

    TypeVector arguments;
    arguments.push_back(ownerType);
    arguments.insert(arguments.end(), types.begin(), types.end());
    method->initializateArguments(arguments);
    return method;
}

MethodPtr Method::inherit(TypePtr ownerType, MethodPtr override) {
    MethodPtr method = MethodPtr(new Method(ownerType, override));
    method->initializateArguments(ownerType, method->m_args);
    return method;
}

FieldPtr Field::create(TypePtr ownerType, TypePtr fieldType, const Identifier& name) {
    FieldPtr field = FieldPtr(new Field(name, ownerType, fieldType));
    ownerType->getMetadata()->fields().insert(field);
    return field;
}

FieldPtr Field::inherit(TypePtr ownerType, FieldPtr override) {
    FieldPtr field = FieldPtr(new Field(ownerType, override));
    return field;
}

// create unary operator
UnaryPtr UnaryOperator::create(TypePtr ownerType, UnaryOpcode opcode, TypePtr returnType) {
    UnaryPtr op = UnaryPtr(new UnaryOperator(opcode, ownerType, returnType));
    ownerType->getMetadata()->unary().insert(op);

    TypeVector arguments;
    arguments.push_back(ownerType);
    op->initializateArguments(arguments);
    return op;
}

// create binary operator
BinaryPtr BinaryOperator::create(TypePtr ownerType, BinaryOpcode opcode, TypePtr returnType, TypePtr operandType) {
    BinaryPtr op = BinaryPtr(new BinaryOperator(opcode, ownerType, returnType));
    ownerType->getMetadata()->binary().insert(op);

    TypeVector arguments;
    arguments.push_back(ownerType);
    arguments.push_back(operandType);
    op->initializateArguments(arguments);
    return op;
}

// create multiary operator
MultiaryPtr MultiaryOperator::create(TypePtr ownerType, MultiaryOpcode opcode, TypePtr returnType, TypeVector types) {
    MultiaryPtr op = MultiaryPtr(new MultiaryOperator(opcode, ownerType, returnType));
    ownerType->getMetadata()->multiary().insert(op);

    TypeVector arguments;
    arguments.push_back(ownerType);
    arguments.insert(arguments.end(), types.begin(), types.end());
    op->initializateArguments(arguments);
    return op;
}
