/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "ModuleImpl.hpp"
#include "TypeImpl.hpp"
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
: m_typeID((TypeID) 0), m_module(module), m_meta(new TypeImpl(this)) {
    m_module->getMetadata()->types.push_back(this);
}

Type::~Type() {
    delete m_meta;
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
    KIWI_NOT_IMPLEMENT();
}

// add binary operator
BinaryOperator* Type::addBinary(
    Member::BinaryOpcode opcode,
    Type* returnType,
    Type* operandType,
    codegen::CallableEmitter* emitter
) {
    KIWI_NOT_IMPLEMENT();
}

/// add multiary operator
MultiaryOperator* Type::addMultiary(
    Member::MultiaryOpcode opcode,
    Type* returnType,
    std::vector<Type*> arguments,
    codegen::CallableEmitter* emitter
) {
    KIWI_NOT_IMPLEMENT();
}

// add field
Field* Type::addField(const Identifier& name, Type* fieldType) {
    KIWI_NOT_IMPLEMENT();
}

// Merge fields
Field* Type::mergeField(Field* declared, Field* inherited) {
    KIWI_NOT_IMPLEMENT();
}

// add method
Method* Type::addMethod(const Identifier& name, Type* returnType, std::vector<Type*> arguments) {
    KIWI_NOT_IMPLEMENT();
}

// find unary operator
UnaryOperator* Type::findUnary(Member::UnaryOpcode opcode) const {
    KIWI_NOT_IMPLEMENT();
}

// find binary operator
BinaryOperator* Type::findBinary(Member::BinaryOpcode opcode, Type* operandType) const {
    KIWI_NOT_IMPLEMENT();
}

// find binary operator
MultiaryOperator* Type::findMultiary(Member::MultiaryOpcode opcode, std::vector<Type*> arguments) const {
    KIWI_NOT_IMPLEMENT();
}

// find field
Field* Type::findField(const Identifier& name) const {
    KIWI_NOT_IMPLEMENT();
}

// find method
Method* Type::findMethod(const Identifier& name, std::vector<Type*> arguments) const {
    KIWI_NOT_IMPLEMENT();
}

llvm::Type* Type::getVarType() const {
    return m_meta->m_varType;
}

bool Type::isInherit(const Type* type, bool duckCast) const {
    KIWI_NOT_IMPLEMENT();
}

bool Type::isCastableTo(const Type* type, bool duckCast) const {
    KIWI_NOT_IMPLEMENT();
}

CastOperator* Type::findCastTo(const Type* type) const {
    KIWI_NOT_IMPLEMENT();
}

void Type::inheritBase(Type* type) {
    KIWI_NOT_IMPLEMENT();
}

// Emit type structure
void Type::emit() {
    KIWI_NOT_IMPLEMENT();
}
