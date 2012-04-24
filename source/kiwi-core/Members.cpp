#include "ContextImpl.hpp"
#include "kiwi/Codegen/Emitter.hpp"
#include "kiwi/Support/Array.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

/// constructor
Callable::Callable(Type* ownerType, Type* returnType)
: Member(ownerType), m_returnType(returnType) {

}

/// constructor
Callable::Callable(Type* ownerType, Type* returnType, tlist argTypes)
: Member(ownerType), m_returnType(returnType) {
    for (tlist::iterator i = argTypes.begin(); i != argTypes.end(); ++i) {
        Type* type    = *i;
        Argument* arg = new Argument(this, type, m_args.size());
        m_args.push_back(arg);
    }
}

Callable::~Callable() {
    for (std::vector<Argument*>::const_iterator i = m_args.begin(); i != m_args.end(); ++i) {
        Argument* arg = *i;
        delete arg;
    }
}

// constructor
UnaryOperator::UnaryOperator(
    Member::UnaryOpcode opcode,
    Type* ownerType,
    Type* resultType,
    codegen::UnaryEmitter* emitter
) : Callable(ownerType, resultType, makeVector(ownerType, 0)), m_opcode(opcode), m_emitter(emitter) {
    m_memberID = UnaryOperatorID;
}

// destructor
UnaryOperator::~UnaryOperator() {
    delete m_emitter;
}

// constructor
BinaryOperator::BinaryOperator(
    Member::BinaryOpcode opcode,
    Type* ownerType,
    Type* resultType,
    Type* operandType,
    codegen::BinaryEmitter* emitter
) : Callable(ownerType, resultType, makeVector(ownerType, operandType, 0)), m_opcode(opcode), m_emitter(emitter) {
    m_memberID = BinaryOperatorID;
}

// destructor
BinaryOperator::~BinaryOperator() {
    delete m_emitter;
}


// constructor
MultiaryOperator::MultiaryOperator(
    Member::MultiaryOpcode opcode,
    Type* ownerType,
    Type* resultType,
    tlist args,
    codegen::MultiaryEmitter* emitter
) : Callable(ownerType, resultType, makeVector(ownerType, args)), m_opcode(opcode), m_emitter(emitter) {
    m_memberID = MultiaryOperatorID;
}

// destructor
MultiaryOperator::~MultiaryOperator() {
    delete m_emitter;
}

// constructor
Field::Field(const Identifier& name, Type* ownerType, Type* fieldType)
: Member(ownerType), m_name(name), m_fieldType(fieldType) {
    m_memberID = FieldID;
}

// destructor
Field::~Field() {}

// constructor
Method::Method(const Identifier& name, Type* ownerType, Type* resultType, tlist argTypes)
: Callable(ownerType, resultType, argTypes), m_name(name), m_func(0) {
    m_memberID = MethodID;
}

// constructor
Argument::Argument(Callable* owner, Type* type, int32_t position)
: m_owner(owner), m_type(type) { }


/// Check signature
bool Callable::hasSignature(const tlist& argTypes, bool isCast) {
    if (argTypes.size() != m_args.size())
        return false;

    for (int i = 0; i < m_args.size(); ++i) {
        /// @todo Replace for simple check
        if (m_args[i]->getType() != argTypes[i])
            return false;
    }

    return true;
}
