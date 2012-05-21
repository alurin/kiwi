/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Type.hpp"
#include "kiwi/Ancestor.hpp"
#include "kiwi/Argument.hpp"
#include "kiwi/Members.hpp"
#include "kiwi/Support/Iterator.hpp"
#include <iostream>
#include "../TypeImpl.hpp"

using namespace kiwi;

namespace {
    class MemberDumpIterator : public MemberIterator {
        virtual void visit(MethodPtr method);

        virtual void visit(FieldPtr field);
    };

    class AncestorDumpIterator : public AncestorIterator {
        virtual void visit(AncestorPtr ancestor);
    };
}

void AncestorDumpIterator::visit(AncestorPtr ancestor) {
    std::cerr << "    + " << ancestor->getAncestorType()->getName() << "\n";
}

void MemberDumpIterator::visit(MethodPtr method) {
    if (method->isDeclared()) {
        std::cerr << "    + ";
    } else {
        std::cerr << "    * ";
    }

    if (method->isOperator()) {
        std::cerr << Method::getOperatorName(method->getOpcode());
    } else {
        std::cerr << method->getName();
    }
    std::cerr << " : " << method->getReturnType()->getName() << "(";

    bool noFirst = false;
    for (Method::const_iterator j = method->arg_begin(); j != method->arg_end(); ++j) {
        if (noFirst) std::cerr << ", "; else noFirst = true;
        ArgumentPtr arg = *j;
        std::cerr << arg->getName() << " : " << arg->getType()->getName();
    }

    std::cerr << ")\n";
    for (Overridable<Method>::const_iterator j = method->override_begin(); j != method->override_end(); ++j) {
        MethodPtr override = j->lock();
        std::cerr << "      -- " << override->getOwnerType()->getName() << ".@" << method->getName() << "\n";
    }
}

void MemberDumpIterator::visit(FieldPtr field) {
    if (field->isDeclared()) {
        std::cerr << "    + ";
    } else {
        std::cerr << "    * ";
    }

    std::cerr << field->getName() << " : " << field->getFieldType()->getName() << "\n";
    for (Overridable<Field>::const_iterator j = field->override_begin(); j != field->override_end(); ++j) {
        FieldPtr override = j->lock();
        std::cerr << "      -- " << override->getOwnerType()->getName() << ".@" << field->getName() << "\n";
    }
}

// dump information about type
void Type::dump() {
    std::cerr << "type " << getName() << "\n";

    if (hasAncestors()) {
        std::cerr << "  Ancestors:\n";
        AncestorDumpIterator visitor;
        each(visitor);
    }

    if (hasFields()) {
        std::cerr << "  Fields:\n";
        MemberDumpIterator visitor;
        each(static_cast<MethodIterator&>(visitor));
    }

    if (hasMethods()) {
        std::cerr << "  Methods:\n";
        MemberDumpIterator visitor;
        each(static_cast<FieldIterator&>(visitor));
    }
}
