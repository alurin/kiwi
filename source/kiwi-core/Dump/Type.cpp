/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Type.hpp"
#include "kiwi/Argument.hpp"
#include "kiwi/Members.hpp"
#include <iostream>
#include "../TypeImpl.hpp"

using namespace kiwi;

// dump information about type
void Type::dump() {
    std::cerr << "type " << getName() << "\n";

    // dump base types
    if (m_meta->base_begin() != m_meta->base_end())
        std::cerr << "  Bases:\n";
    for (std::set<Type*>::const_iterator i = m_meta->base_begin(); i != m_meta->base_end(); ++i) {
        Type* base = *i;
        std::cerr << "    + " << base->getName() << "\n";
    }

    // dump all fields
    if (m_meta->fields().begin() != m_meta->fields().end())
        std::cerr << "  Fields:\n";
    for (MemberSet<Field>::const_iterator i = m_meta->fields().begin(); i != m_meta->fields().end(); ++i) {
        Field* field = (*i);

        if (field->isDeclared()) {
            std::cerr << "    + ";
        } else {
            std::cerr << "    * ";
        }

        std::cerr << field->getName() << " : " << field->getFieldType()->getName() << "\n";
        for (Overridable<Field>::override_const_iterator j = field->override_begin(); j != field->override_end(); ++j) {
            Field* override = *j;
            std::cerr << "      -- " << override->getOwnerType()->getName() << ".@" << field->getName() << "\n";
        }
    }

    if (m_meta->methods().begin() != m_meta->methods().end())
        std::cerr << "  Methods:\n";
    for (MemberSet<Method>::const_iterator i = m_meta->methods().begin(); i != m_meta->methods().end(); ++i) {
        Method* method = (*i);

        if (method->isDeclared()) {
            std::cerr << "    + ";
        } else {
            std::cerr << "    * ";
        }

        std::cerr << method->getName() << " : " << method->getReturnType()->getName() << "(";

        bool noFirst = false;
        for (Callable::const_iterator j = method->arg_begin(); j != method->arg_end(); ++j) {
            if (noFirst) std::cerr << ", "; else noFirst = true;
            Argument* arg = *j;
            std::cerr << arg->getName() << " : " << arg->getType()->getName();
        }

        std::cerr << ")\n";
        for (Overridable<Method>::override_const_iterator j = method->override_begin(); j != method->override_end(); ++j) {
            Method* override = *j;
            std::cerr << "      -- " << override->getOwnerType()->getName() << ".@" << method->getName() << "\n";
        }
    }
}
