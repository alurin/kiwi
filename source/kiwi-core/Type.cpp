/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include "kiwi/assert.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Array.hpp"
#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Instruction.h>
#include <llvm/Module.h>
#include <llvm/ADT/ArrayRef.h>

using namespace kiwi;
using namespace kiwi::codegen;

#define KIWI_CONDITIONAL(__cond, __msg) do { if (!(__cond)) throw __msg; } while(false)

namespace {
    class InheritField {
    public:
        InheritField(Type* type);

        void operator()(Field* field);
    private:
        Type* m_type;
    };

    /// Inherit field
    InheritField::InheritField(Type* type) : m_type(type) {
    }

    void InheritField::operator()(Field* field) {
        // m_type->inheritField(field);
        KIWI_DUMP("Inherit field " << field->getOwnerType()->getName() << "." << field->getName());
    }
}

Type::Type(Module* module)
: m_typeID((TypeID) 0), m_module(module), m_meta(this) {
    m_module->getMetadata()->types.push_back(this);
}

Type::~Type() {
    for (std::vector<UnaryOperator*>::const_iterator i = m_unary.begin(); i != m_unary.end(); ++i) {
        UnaryOperator* op = *i;
        delete op;
    }

    for (std::vector<BinaryOperator*>::const_iterator i = m_binary.begin(); i != m_binary.end(); ++i) {
        BinaryOperator* op = *i;
        delete op;
    }

    for (std::vector<MultiaryOperator*>::const_iterator i = m_multiary.begin(); i != m_multiary.end(); ++i) {
        MultiaryOperator* op = *i;
        delete op;
    }
    for (std::vector<Method*>::const_iterator i = m_methods.begin(); i != m_methods.end(); ++i) {
        Method* method = *i;
        delete method;
    }
}

Context* Type::getContext() const {
    return m_module->getContext();
}

// add binary operator
UnaryOperator* Type::addUnary(
    Member::UnaryOpcode opcode,
    Type* returnType,
    codegen::CallableEmitter* emitter
) {
    UnaryOperator* op = new UnaryOperator(opcode, this, returnType, emitter);
    m_unary.push_back(op);
    return op;
}

// add binary operator
BinaryOperator* Type::addBinary(
    Member::BinaryOpcode opcode,
    Type* returnType,
    Type* operandType,
    codegen::CallableEmitter* emitter
) {
    BinaryOperator* op = new BinaryOperator(opcode, this, returnType, operandType, emitter);
    m_binary.push_back(op);
    return op;
}

/// add multiary operator
MultiaryOperator* Type::addMultiary(
    Member::MultiaryOpcode opcode,
    Type* returnType,
    std::vector<Type*> arguments,
    codegen::CallableEmitter* emitter
) {
    MultiaryOperator* op = new MultiaryOperator(opcode, this, returnType, arguments, emitter);
    m_multiary.push_back(op);
    return op;
}

// add field
Field* Type::addField(const Identifier& name, Type* fieldType) {
    // redeclare
    Field* declared = findField(name);
    if (declared && fieldType == declared->getFieldType()) {
        return declared;
    }

    // declare new field
    Field* field = new Field(name, this, fieldType);
    m_fields.insert(field);
    onInsertField(field);
    return field;
}

// Merge fields
Field* Type::mergeField(Field* declared, Field* inherited) {
    KIWI_CONDITIONAL(this == declared->getOwnerType(),              "Field not declared in class"                   );
    KIWI_CONDITIONAL(this->isInherit(inherited->getOwnerType()),    "Field not inherited from one of parent classes");
    // KIWI_CONDITIONAL(declared->isMathSignature(inherit),            "Fields signatures not equal"                   );
    m_fields.merge(declared, inherited);
}

// add method
Method* Type::addMethod(const Identifier& name, Type* returnType, std::vector<Type*> arguments) {
    Method* method = new Method(name, this, returnType, arguments);
    m_methods.push_back(method);
    return method;
}

// find unary operator
UnaryOperator* Type::findUnary(Member::UnaryOpcode opcode) const {
    for (std::vector<UnaryOperator*>::const_iterator i = m_unary.begin(); i != m_unary.end(); ++i) {
        UnaryOperator* op = *i;
        if (op->getOpcode() == opcode&& op->hasSignature(makeVector(const_cast<Type*>(this), 0), true)) {
            return op;
        }
    }
    return 0;
}

// find binary operator
BinaryOperator* Type::findBinary(Member::BinaryOpcode opcode, Type* operandType) const {
    for (std::vector<BinaryOperator*>::const_iterator i = m_binary.begin(); i != m_binary.end(); ++i) {
        BinaryOperator* op = *i;
        if (op->getOpcode() == opcode && op->hasSignature(makeVector(const_cast<Type*>(this), operandType, 0), true)) {
            return op;
        }
    }
    return 0;
}

// find binary operator
MultiaryOperator* Type::findMultiary(Member::MultiaryOpcode opcode, std::vector<Type*> arguments) const {
    for (std::vector<MultiaryOperator*>::const_iterator i = m_multiary.begin(); i != m_multiary.end(); ++i) {
        MultiaryOperator* op = *i;
        if (op->getOpcode() == opcode && op->hasSignature(makeVector(const_cast<Type*>(this), arguments), true)) {
            return op;
        }
    }
    return 0;
}

// find field
Field* Type::findField(const Identifier& name) const {
    for (MemberSet<Field>::const_iterator i = m_fields.begin(); i != m_fields.end(); ++i) {
        Field* field = *i;
        if (field->getName() == name) {
            return field;
        }
    }
    return 0;
}

// find method
Method* Type::findMethod(const Identifier& name, std::vector<Type*> arguments) const {
    for (std::vector<Method*>::const_iterator i = m_methods.begin(); i != m_methods.end(); ++i) {
        Method* method = *i;
        if (method->getName() == name && method->hasSignature(makeVector(const_cast<Type*>(this), arguments), true)) {
            return method;
        }
    }
    return 0;
}

llvm::Type* getVarType() const {
    return m_meta->m_varType;
}

bool Type::isInherit(const Type* type, bool duckCast) const {
    return false;
}

bool Type::isCastableTo(const Type* type, bool duckCast) const {
    return false;
}

CastOperator* Type::findCastTo(const Type* type) const {
    throw "Not implemented";
}

void Type::inheritBase(Type* type) {
    if (type != this) {
        m_fields.merge(type->m_fields);

        // connect listeners
        onInsertField.connect(InheritField(type));
    }
}

// Emit type structure
void Type::emit() {
}
