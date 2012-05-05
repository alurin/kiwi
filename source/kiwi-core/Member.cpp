/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi/Member.hpp"

using namespace kiwi;

// cosntructor
Member::Member(TypePtr type)
: m_memberID((MemberID) 0), m_ownerType(type) {
}

// destructor
Member::~Member() {
}

Identifier Member::getOperatorName(MethodOpcode opcode) {
    switch (opcode) {
        case Pos:
            return "Pos [+]";
        case Neg:
            return "Neg [-]";
        case Not:
            return "Not [!]";
        case Dec:
            return "Dec [++]";
        case Inc:
            return "Inc [11]";
        case Print:
            return "Print";
        case Add:
            return "Add [+]";
        case Sub:
            return "Sub [-]";
        case Mul:
            return "Mul [*]";
        case Div:
            return "Div [/]";
        case Lsh:
            return "Lsh [<<]";
        case Rsh:
            return "Rsh [>>]";
        case Or:
            return "Or [|]";
        case And:
            return "And [&]";
        case Eq:
            return "Eq [==]";
        case Neq:
            return "Neq [!=]";
        case Ge:
            return "Ge [>=]";
        case Le:
            return "Le [>=]";
        case Gt:
            return "Gt [>]";
        case Lt:
            return "Lt [<]";
        case Constructor:
            return "Constructor";
        case Subtraction:
            return "Subtraction";
        case Invoke:
            return "Invoke";
        case Subroutine:
            return "Method";
        case Append:
            return "Append";
        default:
            return "unknown";
    };
}
