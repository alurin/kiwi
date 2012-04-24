#ifndef KIWI_MEMBER_INCLUDED
#define KIWI_MEMBER_INCLUDED

#include "kiwi/Config.hpp"

namespace llvm
{
    class Type;
    class Function;
    class GlobalVariable;
}

namespace kiwi
{
    class Type;

    /// Type member
    class Member {
    public:
        ///
        enum MemberID {
            FieldID = 1,
            MethodID,
            BinaryOperatorID,
            UnaryOperatorID,
            MultiaryOperatorID,
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
            // Append,      // [   ] =
            Subtraction, // [...]
            Invoke       // (   )
        };
    public:
        /// virtual destructor
        virtual ~Member();

        /// Returns owner type
        Type* getOwnerType() const {
            return m_ownerType;
        }

        /// get member class identifier
        MemberID getMemberID() const {
            return m_memberID;
        }
    protected:
        /// member class identifier
        MemberID m_memberID;

        /// member owner type
        Type* m_ownerType;

        /// cosntructor
        Member(Type* type);
    };
}

#endif
