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

using namespace kiwi;
using namespace kiwi::codegen;

#define KIWI_CONDITIONAL(__cond, __msg) do { if (!(__cond)) throw __msg; } while(false)

#define TYPE_IMPLEMENTATION_FINDERS(_name, _type, _method) \
    void Type::merge ## _name(_type declared, _type inherited) { \
        m_meta->_method().merge(declared, inherited); \
    }


TYPE_IMPLEMENTATION_FINDERS(Field, FieldPtr, fields)

namespace {
    /// Finder
    class UnaryFinder {
    public:
        /// constructor
        UnaryFinder(Member::UnaryOpcode opcode) : m_opcode(opcode) {
        }

        /// conditional for find
        bool operator()(UnaryPtr op) {
            return op->getOpcode() == m_opcode;
        }
    private:
        /// opcode
        Member::UnaryOpcode m_opcode;
    };

    class BinaryFinder {
    public:
        BinaryFinder(Member::BinaryOpcode opcode, TypePtr operandType)
        : m_opcode(opcode), m_operandType(operandType) {
        }

        bool operator()(BinaryPtr op) {
            return op->getOpcode() == m_opcode && m_operandType == op->getArgument(1)->getType();
        }
    protected:
        Member::BinaryOpcode m_opcode;
        TypePtr m_operandType;
    };

    class MultiaryFinder {
    public:
        MultiaryFinder(Member::MultiaryOpcode opcode, std::vector<TypePtr> arguments)
        : m_opcode(opcode), m_arguments(arguments) {
        }

        bool operator()(MultiaryPtr op) {
            return op->getOpcode() == m_opcode && op->hasSignature(m_arguments);
        }

    protected:
        Member::MultiaryOpcode m_opcode;
        std::vector<TypePtr> m_arguments;
    };

    class FieldFinder {
    public:
        FieldFinder(const Identifier& name)
        : m_name(name) {
        }

        bool operator()(FieldPtr field) {
            return field->getName() == m_name;
        }

    protected:
        Identifier m_name;
    };

    class MethodFinder {
    public:
        MethodFinder(const Identifier& name, std::vector<TypePtr> arguments)
        : m_name(name), m_arguments(arguments) {
        }

        bool operator()(MethodPtr method) {
            return method->getName() == m_name && method->hasSignature(m_arguments);
        }
    protected:
        Identifier m_name;
        std::vector<TypePtr> m_arguments;
    };

}

Type::Type(ModulePtr module)
: m_typeID((TypeID) 0), m_module(module), m_meta(new TypeImpl(this)) {
}

Type::~Type() {
    delete m_meta;
}

ContextPtr Type::getContext() const {
    return getModule()->getContext();
}

// add binary operator
UnaryPtr Type::addUnary(Member::UnaryOpcode opcode, TypePtr returnType) {
    return UnaryOperator::create(shared_from_this(), opcode, returnType);
}

// add binary operator
BinaryPtr Type::addBinary(Member::BinaryOpcode opcode, TypePtr returnType, TypePtr operandType) {
    return BinaryOperator::create(shared_from_this(), opcode, returnType, operandType);
}

/// add multiary operator
MultiaryPtr Type::addMultiary(Member::MultiaryOpcode opcode, TypePtr returnType, std::vector<TypePtr> arguments) {
    return MultiaryOperator::create(shared_from_this(), opcode, returnType, arguments);
}

// add field
FieldPtr Type::addField(const Identifier& name, TypePtr fieldType) {
    return Field::create(shared_from_this(), fieldType, name);
}

// add method
MethodPtr Type::addMethod(const Identifier& name, TypePtr returnType, std::vector<TypePtr> arguments) {
    return Method::create(shared_from_this(), returnType, arguments, name);
}

// find unary operator
UnaryPtr Type::findUnary(Member::UnaryOpcode opcode) const {
    return find_if(m_meta->unary(), UnaryFinder(opcode));
}

// find binary operator
BinaryPtr Type::findBinary(Member::BinaryOpcode opcode, TypePtr operandType) const {
    return find_if(m_meta->binary(), BinaryFinder(opcode, operandType));
}

// find binary operator
MultiaryPtr Type::findMultiary(Member::MultiaryOpcode opcode, std::vector<TypePtr> types) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.insert(arguments.end(), types.begin(), types.end());
    return find_if(m_meta->multiary(), MultiaryFinder(opcode, arguments));
}

// find field
FieldPtr Type::findField(const Identifier& name) const {
    return find_if(m_meta->fields(), FieldFinder(name));
}

// find method
MethodPtr Type::findMethod(const Identifier& name, std::vector<TypePtr> types) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.insert(arguments.end(), types.begin(), types.end());
    return find_if(m_meta->methods(), MethodFinder(name, arguments));
}

llvm::Type* Type::getVarType() const {
    return m_meta->varType;
}

bool Type::isInherit(const TypePtr type, bool duckCast) const {
    return m_meta->isBase(type);
}

bool Type::isCastableTo(const TypePtr type, bool duckCast) const {
    return m_meta->isBase(type);
}

// return size of fields set
size_t Type::field_size() const {
    return m_meta->fields().size();
}

// Emit type structure
void Type::emit() {
}
