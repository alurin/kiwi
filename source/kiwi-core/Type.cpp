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
#include "kiwi/Type.hpp"
#include "kiwi/Argument.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Array.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

#define KIWI_CONDITIONAL(__cond, __msg) do { if (!(__cond)) throw __msg; } while(false)

#define TYPE_IMPLEMENTATION_FINDERS(_name, _type, _method) \
    void Type::merge ## _name(_type* declared, _type* inherited) { \
        m_meta->_method().merge(declared, inherited); \
    }


TYPE_IMPLEMENTATION_FINDERS(Field, Field, fields)

namespace {
    /// Finder
    class UnaryFinder {
    public:
        /// constructor
        UnaryFinder(Member::UnaryOpcode opcode) : m_opcode(opcode) {
        }

        /// conditional for find
        bool operator()(UnaryOperator* op) {
            return op->getOpcode() == m_opcode;
        }
    private:
        /// opcode
        Member::UnaryOpcode m_opcode;
    };

    class BinaryFinder {
    public:
        BinaryFinder(Member::BinaryOpcode opcode, Type* operandType)
        : m_opcode(opcode), m_operandType(operandType) {
        }

        bool operator()(BinaryOperator* op) {
            return op->getOpcode() == m_opcode && m_operandType == op->getArgument(1)->getType();
        }
    protected:
        Member::BinaryOpcode m_opcode;
        Type* m_operandType;
    };

    class MultiaryFinder {
    public:
        MultiaryFinder(Member::MultiaryOpcode opcode, std::vector<Type*> arguments)
        : m_opcode(opcode), m_arguments(arguments) {
        }

        bool operator()(MultiaryOperator* op) {
            return op->getOpcode() == m_opcode && op->hasSignature(m_arguments);
        }

    protected:
        Member::MultiaryOpcode m_opcode;
        std::vector<Type*> m_arguments;
    };

    class FieldFinder {
    public:
        FieldFinder(const Identifier& name)
        : m_name(name) {
        }

        bool operator()(Field* field) {
            return field->getName() == m_name;
        }

    protected:
        Identifier m_name;
    };

    class MethodFinder {
    public:
        MethodFinder(const Identifier& name, std::vector<Type*> arguments)
        : m_name(name), m_arguments(arguments) {
        }

        bool operator()(Method* method) {
            return method->getName() == m_name && method->hasSignature(m_arguments);
        }
    protected:
        Identifier m_name;
        std::vector<Type*> m_arguments;
    };

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
    Type* returnType
) {
    return new UnaryOperator(opcode, this, returnType);
}

// add binary operator
BinaryOperator* Type::addBinary(
    Member::BinaryOpcode opcode,
    Type* returnType,
    Type* operandType
) {
    return new BinaryOperator(opcode, this, returnType, operandType);
}

/// add multiary operator
MultiaryOperator* Type::addMultiary(
    Member::MultiaryOpcode opcode,
    Type* returnType,
    std::vector<Type*> arguments
) {
    return new MultiaryOperator(opcode, this, returnType, arguments);
}

// add field
Field* Type::addField(const Identifier& name, Type* fieldType) {
    return new Field(name, this, fieldType);
}

// add method
Method* Type::addMethod(const Identifier& name, Type* returnType, std::vector<Type*> arguments) {
    return new Method(name, this, returnType, arguments);
}

// find unary operator
UnaryOperator* Type::findUnary(Member::UnaryOpcode opcode) const {
    return find_if(m_meta->unary(), UnaryFinder(opcode));
}

// find binary operator
BinaryOperator* Type::findBinary(Member::BinaryOpcode opcode, Type* operandType) const {
    return find_if(m_meta->binary(), BinaryFinder(opcode, operandType));
}

// find binary operator
MultiaryOperator* Type::findMultiary(Member::MultiaryOpcode opcode, std::vector<Type*> arguments) const {
    return find_if(m_meta->multiary(), MultiaryFinder(opcode, makeVector(const_cast<Type*>(this), arguments)));
}

// find field
Field* Type::findField(const Identifier& name) const {
    return find_if(m_meta->fields(), FieldFinder(name));
}

// find method
Method* Type::findMethod(const Identifier& name, std::vector<Type*> arguments) const {
    return find_if(m_meta->methods(), MethodFinder(name, makeVector(const_cast<Type*>(this), arguments)));
}

llvm::Type* Type::getVarType() const {
    return m_meta->varType;
}

bool Type::isInherit(const Type* type, bool duckCast) const {
    return m_meta->isBase(type);
}

bool Type::isCastableTo(const Type* type, bool duckCast) const {
    return m_meta->isBase(type);
}

// Emit type structure
void Type::emit() {
}
