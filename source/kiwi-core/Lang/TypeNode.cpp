/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "Driver.hpp"
#include "TypeNode.hpp"
#include "kiwi/Module.hpp"
#include "kiwi/Type.hpp"
#include <cstdio>

using namespace kiwi;
using namespace kiwi::lang;

TypeNode::TypeNode() {
}

TypeNode::~TypeNode() {
}

ConcreteTypeNode::ConcreteTypeNode(Type* type)
: m_type(type) {
}


QualifiedTypeNode::QualifiedTypeNode(const Identifier& name)
: m_name(name) {
}

Type* QualifiedTypeNode::get(Driver& driver) {
    Module* module = driver.getModule();
    Type*   type   = module->find(m_name);
    if (!type) {
        throw LangException()
            << exception_format("Type '%1%' not found", m_name)
            << exception_location(to_location(this));
    }
    return type;
}
