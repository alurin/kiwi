/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_MEMBER_INCLUDED
#define KIWI_MEMBER_INCLUDED

#include "kiwi/types.hpp"

namespace kiwi
{
    /// Type member
    class Member : public boost::enable_shared_from_this<Member>, public boost::noncopyable  {
    public:
        ///
        enum MemberID {
            FieldID = 1,
            MethodID,
            CastID
        };

        /// Unary operation code
        enum MethodOpcode {
            /// Unary operations opcodes
            Pos = 1,
            Neg,
            Not,
            Dec,  // [ Not implemented                  ]
            Inc,  // [ Not implemented                  ]
            Print, // [ Remove in favor of console.print ]

            /// Binary operations opcodes
            Add,
            Sub,
            Mul,
            Div,
            Lsh,
            Rsh,
            Or,
            And,
            Eq,
            Neq,
            Ge,
            Le,
            Gt,
            Lt,

            /// Multiary operations opcodes
            Subroutine,         // simple method
            Constructor,        // ctore
            Append,             // [...] =
            Subtraction,        // = [...]
            Invoke,             // (   )

            /// Information about
            UnaryFirstElement   = Pos,
            UnaryLastElement    = Print,
            BinaryFirstElement  = Add,
            BinaryLastElement   = Lt,
            // CompareFirstElement = Or,
            // CompareLastElement  = Lt
        };
    public:
        /// virtual destructor
        virtual ~Member();

        /// Returns owner type
        TypePtr getOwnerType() const {
            return m_ownerType.lock();
        }

        /// get member class identifier
        MemberID getMemberID() const {
            return m_memberID;
        }

        /// Parent class contains equal member with name(optional) and signature
        bool isInherit() const;

        /// temp: get name of operator by opcode
        static Identifier getOperatorName(MethodOpcode opcode);
    protected:
        /// member class identifier
        MemberID m_memberID;

        /// member owner type
        TypeWeak m_ownerType;

        /// cosntructor
        Member(TypePtr type);
    };
}

#endif
