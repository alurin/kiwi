#include "ContextMeta.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "codegen/LlvmEmitter.hpp"
#include <llvm/DerivedTypes.h>
#include <llvm/Instruction.h>

using namespace kiwi;
using namespace kiwi::codegen;

Type::Type(ModuleRef module)
: m_module(module), m_varType(0) { }

Type::~Type() { }

// constructor
UnaryOperator::UnaryOperator(
    UnaryOperator::Opcode opcode,
    TypeRef resultType,
    codegen::UnaryEmitter* emitter
) : m_opcode(opcode), m_resultType(resultType), m_emitter(emitter)
{ }

// constructor
BinaryOperator::BinaryOperator(
    BinaryOperator::Opcode opcode,
    TypeRef resultType,
    TypeRef operatorType,
    codegen::BinaryEmitter* emitter
) : m_opcode(opcode), m_resultType(resultType), m_operatorType(operatorType), m_emitter(emitter)
{ }

// add binary operator
UnaryRef Type::add(
    UnaryOperator::Opcode opcode,
    TypeRef resultType,
    codegen::UnaryEmitter* emitter
) {
    UnaryRef op = UnaryRef(new UnaryOperator(opcode, resultType, emitter));
    m_unary.push_back(op);
    return op;
}

// add binary operator
BinaryRef Type::add(
    BinaryOperator::Opcode opcode,
    TypeRef resultType,
    TypeRef operatorType,
    codegen::BinaryEmitter* emitter
) {
    BinaryRef op = BinaryRef(new BinaryOperator(opcode, resultType, operatorType, emitter));
    m_binary.push_back(op);
    return op;
}

// find unary operator
UnaryRef Type::find(UnaryOperator::Opcode opcode)
{
    for (std::vector<UnaryRef>::iterator i = m_unary.begin(); i != m_unary.end(); ++i)
    {
        UnaryRef op = *i;
        if (op->getOpcode() == opcode) {
            return op;
        }
    }
    return UnaryRef();
}

// find binary operator
BinaryRef Type::find(BinaryOperator::Opcode opcode, TypeRef operatorType)
{
    for (std::vector<BinaryRef>::iterator i = m_binary.begin(); i != m_binary.end(); ++i)
    {
        BinaryRef op = *i;
        if (op->getOpcode() == opcode && operatorType == op->getOperatorType()) {
            return op;
        }
    }
    return BinaryRef();
}
