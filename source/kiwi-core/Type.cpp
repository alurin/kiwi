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
#include "kiwi/Exception.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

#define KIWI_CONDITIONAL(__cond, __msg) do { if (!(__cond)) throw __msg; } while(false)

#define TYPE_IMPLEMENTATION_FINDERS(_name, _type, _method) \
    void Type::merge ## _name(_type declared, _type inherited) { \
        m_meta->_method().merge(declared, inherited); \
    }

TYPE_IMPLEMENTATION_FINDERS(Field, FieldPtr, fields)

namespace {

    /// Field finder
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
        : m_name(name), m_arguments(arguments), m_opcode(Member::Subroutine) {
        }

        MethodFinder(Member::MethodOpcode opcode, std::vector<TypePtr> arguments)
        :  m_arguments(arguments), m_opcode(opcode) {
        }

        bool operator()(MethodPtr method) {
            return m_opcode == method->getOpcode() && method->getName() == m_name && method->hasSignature(m_arguments);
        }
    protected:
        Member::MethodOpcode m_opcode;
        Identifier m_name;
        std::vector<TypePtr> m_arguments;
    };

}

Type::Type(ModulePtr module)
: m_typeID((TypeID) 0), m_module(module), m_meta(new TypeImpl(this, module)) {
}

Type::~Type() {
    delete m_meta;
}

ContextPtr Type::getContext() const {
    return getModule()->getContext();
}

// add binary operator
MethodPtr Type::addUnary(Member::MethodOpcode opcode, TypePtr returnType) {
    std::vector<TypePtr> arguments;
    return Method::create(shared_from_this(), returnType, arguments, opcode);
}

// add binary operator
MethodPtr Type::addBinary(Member::MethodOpcode opcode, TypePtr returnType, TypePtr operandType) {
    std::vector<TypePtr> arguments;
    arguments.push_back(operandType);
    return Method::create(shared_from_this(), returnType, arguments, opcode);
}

/// add multiary operator
MethodPtr Type::addMultiary(Member::MethodOpcode opcode, TypePtr returnType, std::vector<TypePtr> arguments) {
    return Method::create(shared_from_this(), returnType, arguments, opcode);
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
MethodPtr Type::findUnary(Member::MethodOpcode opcode) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    return find_if(m_meta->methods(), MethodFinder(opcode, arguments));
}

// find binary operator
MethodPtr Type::findBinary(Member::MethodOpcode opcode, TypePtr operandType) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.push_back(operandType);
    return find_if(m_meta->methods(), MethodFinder(opcode, arguments));
}

// find binary operator
MethodPtr Type::findMultiary(Member::MethodOpcode opcode, std::vector<TypePtr> types) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.insert(arguments.end(), types.begin(), types.end());
    return find_if(m_meta->methods(), MethodFinder(opcode, arguments));
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

/// find method
MethodPtr Type::findMethod(Member::MethodOpcode opcode, std::vector<TypePtr> types) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.insert(arguments.end(), types.begin(), types.end());
    return find_if(m_meta->methods(), MethodFinder(opcode, arguments));
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

void* Type::getVTablePointer(TypePtr type) {
    if (type.get() == this)
        return m_meta->getVirtualTable().getPointer();
    else if (m_meta->isBase(type)) {

    }

    BOOST_THROW_EXCEPTION(Exception() << exception_message("Received type is not base for current type"));
}

void* Type::getAMapPointer(TypePtr type) {
    if (type.get() == this)
        return m_meta->getAddressMap().getPointer();
    else if (m_meta->isBase(type)) {

    }

    BOOST_THROW_EXCEPTION(Exception() << exception_message("Received type is not base for current type"));
}

// Emit type structure
void Type::update() {

}
