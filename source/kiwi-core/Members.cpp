/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "ContextImpl.hpp"
#include "TypeImpl.hpp"
#include "Codegen/LlvmEmitter.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Type.hpp"
#include "kiwi/Argument.hpp"
#include "kiwi/Context.hpp"
#include "kiwi/Exception.hpp"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Function.h>

using namespace kiwi;
using namespace kiwi::codegen;

// constructor
Field::Field(TypePtr ownerType, FieldPtr field)
: Member(ownerType), m_name(field->getName()), m_fieldType(field->getFieldType()), Overridable<Field>(false) {
    override(field);
}

// constructor
Field::Field(const Identifier& name, TypePtr ownerType, TypePtr fieldType)
: Member(ownerType), m_name(name), m_fieldType(fieldType), Overridable<Field>(true) {
    m_memberID = FieldID;
}

// constructor
Method::Method(const Identifier& name, TypePtr ownerType, TypePtr returnType)
: Member(ownerType), m_returnType(returnType), Overridable<Method>(true), m_name(name), m_opcode(Subroutine)
, m_policy(0), m_func(0), m_pointerTo(0), m_position(-1) {
    m_memberID = MethodID;
}

// constructor
Method::Method(MethodOpcode opcode, TypePtr ownerType, TypePtr returnType)
: Member(ownerType), m_returnType(returnType), Overridable<Method>(true), m_opcode(opcode)
, m_policy(0), m_func(0), m_pointerTo(0), m_position(-1) {
    m_memberID = MethodID;
}

// constructor
Method::Method(TypePtr ownerType, MethodPtr method)
: Member(ownerType), m_returnType(method->getReturnType()), Overridable<Method>(false), m_name(method->getName())
, m_opcode(method->getOpcode()), m_policy(new CloneEmitter(method)), m_func(0), m_pointerTo(0), m_position(-1) {
    override(method);
}

// destructor
Method::~Method() {
    delete m_policy;
}

// Create method add register in type
MethodPtr Method::create(TypePtr ownerType, TypePtr returnType, std::vector<TypePtr> types, const Identifier& name) {
    MethodPtr method = MethodPtr(new Method(name, ownerType, returnType));
    ownerType->getMetadata()->methods().insert(method);

    TypeVector arguments;
    arguments.push_back(ownerType);
    arguments.insert(arguments.end(), types.begin(), types.end());
    method->initializateArguments(arguments);
    return method;
}

MethodPtr Method::create(TypePtr ownerType, TypePtr returnType, std::vector<TypePtr> types, const MethodOpcode& opcode) {
    kiwi_assert(!(Member::UnaryFirstElement   <= opcode && opcode <= Member::UnaryLastElement  ) || types.size() == 0,
        "Unary operator has only one arguments");
    kiwi_assert(!(Member::BinaryFirstElement  <= opcode && opcode <= Member::BinaryLastElement ) || types.size() == 1,
        "Binary operator has only two arguments");

    MethodPtr method = MethodPtr(new Method(opcode, ownerType, returnType));
    ownerType->getMetadata()->methods().insert(method);

    TypeVector arguments;
    arguments.push_back(ownerType);
    arguments.insert(arguments.end(), types.begin(), types.end());
    method->initializateArguments(arguments);
    return method;
}

MethodPtr Method::inherit(TypePtr ownerType, MethodPtr override) {
    MethodPtr method = MethodPtr(new Method(ownerType, override));
    method->initializateArguments(ownerType, method->m_args);
    return method;
}

FieldPtr Field::create(TypePtr ownerType, TypePtr fieldType, const Identifier& name) {
    FieldPtr field = FieldPtr(new Field(name, ownerType, fieldType));
    ownerType->getMetadata()->fields().insert(field);
    return field;
}

FieldPtr Field::inherit(TypePtr ownerType, FieldPtr override) {
    FieldPtr field = FieldPtr(new Field(ownerType, override));
    return field;
}

// Check signature
bool Method::hasSignature(const TypeVector& types, bool isCast) const {
    if (types.size() != m_args.size())
        return false;

    for (int i = 0; i < m_args.size(); ++i) {
        /// @todo Replace for simple check
        if (m_args[i]->getType() != types[i])
            if (!types[i]->isCastableTo(m_args[i]->getType()))
                return false;
    }

    return true;
}

// set function
void Method::setFunction(llvm::Function* func) {
    m_func = func;
    /// @todo What if, policy already exists at this point?
    if (!getPolicy()) {
        setPolicy(new LlvmCallEmitter(MethodPtr(shared_from_this(), this), m_returnType.lock()));
    }
}

// return method position in vtable
int32_t Method::getPosition() const {
    return m_position;
}

// return pointer to function
void* Method::getPointerTo() const {
    if (m_pointerTo) {
        return m_pointerTo;
    }

    // map vtable to pointer
    if (m_func) {
        if (m_func->empty()) {
            return 0;
        }
        ContextImpl* meta             = getOwnerType()->getContext()->getMetadata();
        llvm::ExecutionEngine* engine = meta->getBackendEngine();
        kiwi_assert(m_func, "Abstract function has not have a JIT stub");
        m_pointerTo                   = engine->getPointerToFunctionOrStub(m_func);
        return m_pointerTo;
    } else if (m_overrides.size() == 1) {
        MethodPtr parent = m_overrides.begin()->lock();
        return parent->getPointerTo();
    } else {
        BOOST_THROW_EXCEPTION(Exception()
            << exception_format("Abstract method %0%::%1%", getOwnerType()->getName() % getName()));
    }
    return 0;
}

void Method::initializateArguments(TypeVector types) {
    for (TypeVector::iterator i = types.begin(); i != types.end(); ++i) {
        TypePtr type = *i;
        ArgumentPtr arg = ArgumentPtr(new Argument(MethodPtr(shared_from_this(), this), type, m_args.size()));
        m_args.push_back(arg);
    }
    kiwi_assert(m_args.size() > 0, "Method must have minimum one argument");
    kiwi_assert(m_args[0]->getType() == m_ownerType.lock(), "First argument for callable must be owner type");
}

void Method::initializateArguments(TypePtr thisType, ArgumentVector args) {
    int j = 0;
    if(0 == args.size()) {
        ArgumentPtr arg = ArgumentPtr(new Argument(MethodPtr(shared_from_this(), this), thisType, 0));
        m_args.push_back(arg);
    }
    for (ArgumentVector::iterator i = args.begin(); i != args.end(); ++i, ++j) {
        if (0 != j) {
            ArgumentPtr oarg = *i;
            ArgumentPtr arg = ArgumentPtr(new Argument(MethodPtr(shared_from_this(), this), oarg->getType(), j));
            m_args.push_back(arg);
        } else {
            ArgumentPtr arg = ArgumentPtr(new Argument(MethodPtr(shared_from_this(), this), thisType, 0));
            m_args.push_back(arg);
        }
    }
    kiwi_assert(m_args.size() > 0, "Method must have minimum one argument");
    kiwi_assert(m_args[0]->getType() == m_ownerType.lock(), "First argument for callable must be owner type");
}

/// @todo Complex method
void Method::complete() {
    getOwnerType()->getMetadata()->onMethodComplete(MethodPtr(shared_from_this(), this));
}
