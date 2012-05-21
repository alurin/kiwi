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
#include "kiwi/Support/Iterator.hpp"

using namespace kiwi;
using namespace kiwi::codegen;

#define KIWI_CONDITIONAL(__cond, __msg) do { if (!(__cond)) throw __msg; } while(false)

#define TYPE_IMPLEMENTATION_FINDERS(_name, _type, _method) \
    void Type::merge ## _name(_type declared, _type inherited) { \
        m_meta->_method().merge(declared, inherited); \
    }

TYPE_IMPLEMENTATION_FINDERS(Field, FieldPtr, getFields)

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

    /// Collect ancessors
    class AncestorPropogation : public AncestorIterator {
    public:
        /// return ancestors
        std::vector<TypePtr> getAncestors() const {
            return m_ancestors;
        }
    protected:
        /// vector of ancestors
        std::vector<TypePtr> m_ancestors;

        /// visitor pattern
        virtual void visit(AncestorPtr ancestor);
    };
}

void AncestorPropogation::visit(AncestorPtr ancestor) {
    TypePtr type = ancestor->getAncestorType();
    m_ancestors.push_back(type);
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

// add multiary operator
MethodPtr Type::addMultiary(Member::MethodOpcode opcode, TypePtr returnType, std::vector<TypePtr> arguments) {
    return Method::create(shared_from_this(), returnType, arguments, opcode);
}

// add field
FieldPtr Type::addField(const Identifier& name, TypePtr fieldType) {
    return Field::create(shared_from_this(), fieldType, name);
}

// add method
MethodPtr Type::addMethod(const Identifier& name, TypePtr returnType, std::vector<TypePtr> arguments) {
    MethodPtr method = findMethod(name, arguments);
    if (method) {
        if (method->getReturnType() != returnType) {
            BOOST_THROW_EXCEPTION(Exception() << exception_message("Method signature vailate"));
        }
        return method;
    }
    return Method::create(shared_from_this(), returnType, arguments, name);
}

// find unary operator
MethodPtr Type::findUnary(Member::MethodOpcode opcode) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    return find_if(m_meta->getMethods(), MethodFinder(opcode, arguments));
}

// find binary operator
MethodPtr Type::findBinary(Member::MethodOpcode opcode, TypePtr operandType) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.push_back(operandType);
    return find_if(m_meta->getMethods(), MethodFinder(opcode, arguments));
}

// find binary operator
MethodPtr Type::findMultiary(Member::MethodOpcode opcode, std::vector<TypePtr> types) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.insert(arguments.end(), types.begin(), types.end());
    return find_if(m_meta->getMethods(), MethodFinder(opcode, arguments));
}

// find field
FieldPtr Type::findField(const Identifier& name) const {
    return find_if(m_meta->getFields(), FieldFinder(name));
}

// find method
MethodPtr Type::findMethod(const Identifier& name, std::vector<TypePtr> types) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.insert(arguments.end(), types.begin(), types.end());
    return find_if(m_meta->getMethods(), MethodFinder(name, arguments));
}

// find method
MethodPtr Type::findMethod(Member::MethodOpcode opcode, std::vector<TypePtr> types) const {
    std::vector<TypePtr> arguments;
    arguments.push_back(const_cast<Type*>(this)->shared_from_this());
    arguments.insert(arguments.end(), types.begin(), types.end());
    return find_if(m_meta->getMethods(), MethodFinder(opcode, arguments));
}

// Add type ancestor
bool Type::addAncestor(TypePtr type) {
    if (type.get() != this && !this->isAncestor(type) && !this->isDerived(type)) {
        // collect ancestors
        std::vector<TypePtr> ancestors;
        {
            AncestorPropogation it;
            type->each(it);
            ancestors = it.getAncestors();
        }

        // add ancestors in this type
        for (int i = 0; i < ancestors.size(); ++i) {
            TypePtr base = ancestors[i];
            if (!this->isAncestor(base)) {
                AncestorPtr ancestor = AncestorPtr(new Ancestor(shared_from_this(), base));
                m_meta->addAncestor(ancestor);
            }
        }

        // add type as ancestor to this type
        AncestorPtr ancestor = AncestorPtr(new Ancestor(shared_from_this(), type));
        return m_meta->addAncestor(ancestor);
    }
    return false;
}

bool Type::isAncestor(const TypePtr type) const {
    return m_meta->isAncestor(type);
}

bool Type::isCastableTo(const TypePtr type, bool duckCast) const {
    return m_meta->isAncestor(type);
}

void* Type::getVTablePointer(TypePtr type) {
    if (0 == type) {
        return m_meta->getVirtualTable().getPointer();
    }
    return m_meta->getAncestorMetadata(type)->getVirtualTable().getPointer();
}

void* Type::getAMapPointer(TypePtr type) {
    if (0 == type) {
        return m_meta->getAddressMap().getPointer();
    }
    return m_meta->getAncestorMetadata(type)->getAddressMap().getPointer();
}

// Emit type structure
void Type::update() {
    if (hasFields()) {
        m_meta->getAddressMap().update();
    }
}

// iterate over type members
void Type::each(MemberIterator& it) {
    each(static_cast<FieldIterator&>(it));
    each(static_cast<MethodIterator&>(it));
}

// iterate over type methods
void Type::each(MethodIterator& it) {
    MemberSet<Method>::const_iterator current = m_meta->getMethods().begin();
    MemberSet<Method>::const_iterator end = m_meta->getMethods().end();
    for (; current != end; ++current) {
        it.visit(*current);
    }
}

// iterate over
void Type::each(FieldIterator& it) {
    MemberSet<Field>::const_iterator current = m_meta->getFields().begin();
    MemberSet<Field>::const_iterator end = m_meta->getFields().end();
    for (; current != end; ++current) {
        it.visit(*current);
    }
}

// iterate over
void Type::each(AncestorIterator& it) {
    AncestorMap::const_iterator current = m_meta->getAncestors().begin();
    AncestorMap::const_iterator end = m_meta->getAncestors().end();
    for (; current != end; ++current) {
        it.visit(current->second);
    }
}

// has type contains ancestors?
bool Type::hasAncestors() const {
    return m_meta->getMethods().empty();
}

// has type contains fields?
bool Type::hasFields() const {
    return m_meta->getFields().empty();
}

// has type contains methods?
bool Type::hasMethods() const {
    return m_meta->getAncestors().empty();
}

// return count of ancestors
size_t Type::getAncestorsCount() const {
    return m_meta->getAncestors().size();
}

// return count of methods
size_t Type::getMethodsCount() const {
    return m_meta->getMethods().size();
}

// return count of fields
size_t Type::getFieldsCount() const {
    return m_meta->getFields().size();
}
