#include "ContextMeta.hpp"
#include "kiwi/codegen/Emitter.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
UnaryOperator::UnaryOperator(
    Member::UnaryOpcode opcode,
    const TypeRef& ownerType,
    const TypeRef& resultType,
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
    const TypeRef& ownerType,
    const TypeRef& resultType,
    const TypeRef& operandType,
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
Field::Field(const Identifier& name, const TypeRef& ownerType, const TypeRef& fieldType)
: Member(ownerType), m_name(name), m_fieldType(fieldType) {
    m_memberID = FieldID;
}

// destructor
Field::~Field() {}

// constructor
Method::Method(const Identifier& name, const TypeRef& ownerType, const TypeRef& resultType, std::vector<ArgumentRef> arguments)
: Member(ownerType), m_name(name), m_resultType(resultType), m_arguments(arguments), m_func(0)
{
    m_memberID = MethodID;
}

// destructor
Method::~Method() {}

// constructor
Argument::Argument(const Identifier& name, const TypeRef& type)
: m_name(name), m_type(type) { }

ArgumentRef Argument::create(const Identifier& name, const TypeRef& type)
{
    ArgumentRef arg = ArgumentRef(new Argument(name, type));
    return arg;
}
