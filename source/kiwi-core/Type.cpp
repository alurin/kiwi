#include "ContextMeta.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Members.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Instruction.h>
#include <llvm/Module.h>
#include <llvm/ADT/ArrayRef.h>

using namespace kiwi;
using namespace kiwi::codegen;

Type::Type(Module* module)
: m_typeID((TypeID) 0), m_module(module), m_varType(0) { }

Type::~Type() { }

// add binary operator
UnaryOperator* Type::add(
    Member::UnaryOpcode opcode,
    Type* resultType,
    codegen::UnaryEmitter* emitter
) {
    UnaryOperator* op = new UnaryOperator(opcode, this, resultType, emitter);
    m_unary.push_back(op);
    return op;
}

// add binary operator
BinaryOperator* Type::add(
    Member::BinaryOpcode opcode,
    Type* resultType,
    Type* operandType,
    codegen::BinaryEmitter* emitter
) {
    BinaryOperator* op = new BinaryOperator(opcode, this, resultType, operandType, emitter);
    m_binary.push_back(op);
    return op;
}

// add field
Field* Type::add(const Identifier& name, Type* fieldType) {
    Field* field = new Field(name, this, fieldType);
    m_fields.push_back(field);
    return field;
}

// add method
Method* Type::add(const Identifier& name, Type* resultType, std::vector<Type*> arguments) {
    Method* method = new Method(name, this, resultType, arguments);
    m_methods.push_back(method);
    return method;
}

// find unary operator
UnaryOperator* Type::find(Member::UnaryOpcode opcode) {
    for (std::vector<UnaryOperator*>::iterator i = m_unary.begin(); i != m_unary.end(); ++i) {
        UnaryOperator* op = *i;
        if (op->getOpcode() == opcode) {
            return op;
        }
    }
    return 0;
}

// find binary operator
BinaryOperator* Type::find(Member::BinaryOpcode opcode, Type* operandType) {
    for (std::vector<BinaryOperator*>::iterator i = m_binary.begin(); i != m_binary.end(); ++i) {
        BinaryOperator* op = *i;
        if (op->getOpcode() == opcode && operandType == op->getOperandType()) {
            return op;
        }
    }
    return 0;
}

// find field
Field* Type::find(const Identifier& name) {
    for (std::vector<Field*>::iterator i = m_fields.begin(); i != m_fields.end(); ++i) {
        Field* field = *i;
        if (field->getName() == name) {
            return field;
        }
    }
    return 0;
}

// find method
Method* Type::find(const Identifier& name, std::vector<Type*> arguments) {
    for (std::vector<Method*>::iterator i = m_methods.begin(); i != m_methods.end(); ++i) {
        Method* method = *i;
        if (method->getName() == name) {
            bool isAccept = true;
            int j         = 0;
            for (Method::const_iterator i = method->begin(); i != method->end(); ++i, ++j) {
                Argument* arg = *i;
                if (arg->getType() != arguments[j]) {
                    isAccept = false;
                    break;
                }
            }

            if (isAccept) return method;
        }
    }
    return 0;
}

// Emit type structure
void Type::emit() {
}
