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
            UnaryOperatorID
        };

        /// Unary operation code
        enum UnaryOpcode {
            POS = 1,
            NEG,
            NOT,
            DEC,
            INC,
            PRINT
        };
        /// Binary operation code
        enum BinaryOpcode {
            ADD = 1,
            SUB,
            MUL,
            DIV,
            LSH,
            RSH,
            OR,
            AND,
            EQ,
            NEQ,
            GE,
            LE,
            GT,
            LT
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
