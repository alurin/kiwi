/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_MEMBER_INCLUDED
#define KIWI_MEMBER_INCLUDED

#include "kiwi/config.hpp"
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
            BinaryID,
            UnaryID,
            MultiaryID,
            CastID
        };

        /// Unary operation code
        enum UnaryOpcode {
            Pos = 1,
            Neg,
            Not,
            Dec,  // [ Not implemented                  ]
            Inc,  // [ Not implemented                  ]
            Print // [ Remove in favor of console.print ]
        };

        /// Binary operation code
        enum BinaryOpcode {
            Add = 1,
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
            Lt
        };

        /// Multiary operation code
        enum MultiaryOpcode {
            Constructor = 1,
            // Append,      // [   ] =
            Subtraction, // [...]
            Invoke       // (   )
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
        static Identifier getOperatorName(UnaryOpcode opcode);

        /// temp: get name of operator by opcode
        static Identifier getOperatorName(BinaryOpcode opcode);

        /// temp: get name of operator by opcode
        static Identifier getOperatorName(MultiaryOpcode opcode);
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
