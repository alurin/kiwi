#ifndef KIWI_MEMBER_INCLUDED
#define KIWI_MEMBER_INCLUDED

#include "kiwi/Config.hpp"

namespace kiwi
{
    typedef boost::shared_ptr<class Type>               TypeRef;
    typedef boost::weak_ptr<class Type>                 TypeWeak;

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
        TypeRef getOwnerType() const {
            return m_ownerType.lock();
        }

        /// get member class identifier
        MemberID getMemberID() const {
            return m_memberID;
        }
    protected:
        /// member class identifier
        MemberID m_memberID;

        /// member owner type
        TypeWeak m_ownerType;

        /// cosntructor
        Member(const TypeRef& type);
    };
}

#endif