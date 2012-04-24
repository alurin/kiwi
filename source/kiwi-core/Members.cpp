#include "ContextImpl.hpp"
#include "kiwi/Codegen/Emitter.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include "kiwi/Support/Array.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

/// constructor
Callable::Callable(Type* ownerType, Type* returnType)
: Member(ownerType), m_returnType(returnType), m_func(0), m_emitter(0) {

}

/// constructor
Callable::Callable(Type* ownerType, Type* returnType, codegen::CallableEmitter* emitter)
: Member(ownerType), m_returnType(returnType), m_func(0), m_emitter(emitter) {

}

/// constructor
Callable::Callable(Type* ownerType, Type* returnType, TypeVector types)
: Member(ownerType), m_returnType(returnType), m_func(0), m_emitter(0) {
    makeArgumentsFromTypes(types);
}

/// constructor
Callable::Callable(Type* ownerType, Type* returnType, TypeVector types, codegen::CallableEmitter* emitter)
: Member(ownerType), m_returnType(returnType), m_func(0), m_emitter(emitter) {
    makeArgumentsFromTypes(types);
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
    Type* resultType,
    codegen::UnaryEmitter* emitter
) : Callable(ownerType, resultType, makeVector(ownerType, 0), emitter), m_opcode(opcode) {
    m_memberID = UnaryOperatorID;
}

// constructor
BinaryOperator::BinaryOperator(
    Member::BinaryOpcode opcode,
    Type* ownerType,
    Type* resultType,
    Type* operandType,
    codegen::BinaryEmitter* emitter
) : Callable(ownerType, resultType, makeVector(ownerType, operandType, 0), emitter), m_opcode(opcode) {
    m_memberID = BinaryOperatorID;
}

// constructor
MultiaryOperator::MultiaryOperator(
    Member::MultiaryOpcode opcode,
    Type* ownerType,
    Type* resultType,
    TypeVector args,
    codegen::CallableEmitter* emitter
) : Callable(ownerType, resultType, makeVector(ownerType, args), emitter), m_opcode(opcode) {
    m_memberID = MultiaryOperatorID;
}

// constructor
Field::Field(const Identifier& name, Type* ownerType, Type* fieldType)
: Member(ownerType), m_name(name), m_fieldType(fieldType) {
    m_memberID = FieldID;
}

// constructor
Method::Method(const Identifier& name, Type* ownerType, Type* resultType, TypeVector types)
: Callable(ownerType, resultType, types), m_name(name) {
    m_memberID = MethodID;
}

// constructor
Argument::Argument(Callable* owner, Type* type, int32_t position)
: m_owner(owner), m_type(type) { }

/// Check signature
bool Callable::hasSignature(const TypeVector& types, bool isCast) {
    if (types.size() != m_args.size())
        return false;

    for (int i = 0; i < m_args.size(); ++i) {
        /// @todo Replace for simple check
        if (m_args[i]->getType() != types[i])
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
        Type* type    = *i;
        Argument* arg = new Argument(this, type, m_args.size());
        m_args.push_back(arg);
    }
}
