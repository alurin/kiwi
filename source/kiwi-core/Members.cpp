#include "ContextMeta.hpp"
#include "kiwi/Codegen/Emitter.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
UnaryOperator::UnaryOperator(
    Member::UnaryOpcode opcode,
    Type* ownerType,
    Type* resultType,
    codegen::UnaryEmitter* emitter
) : Member(ownerType), m_opcode(opcode), m_resultType(resultType), m_emitter(emitter)
{
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
) : Member(ownerType), m_opcode(opcode), m_resultType(resultType), m_operandType(operandType), m_emitter(emitter)
{
    m_memberID = BinaryOperatorID;
}

// destructor
BinaryOperator::~BinaryOperator() {
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
Method::Method(const Identifier& name, Type* ownerType, Type* resultType, std::vector<Type*> arguments)
: Member(ownerType), m_name(name), m_resultType(resultType), m_func(0)
{
    m_memberID = MethodID;
    for (std::vector<Type*>::iterator i = arguments.begin(); i != arguments.end(); ++i)
    {
        Type* type    = *i;
        Argument* arg = new Argument(this, type, m_arguments.size());
        m_arguments.push_back(arg);
    }
}

// destructor
Method::~Method() {}

// constructor
Argument::Argument(Method* owner, Type* type, int32_t position)
: m_owner(owner), m_type(type) { }
