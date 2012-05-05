/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_MEMBERS_INCLUDED
#define KIWI_MEMBERS_INCLUDED

#include "kiwi/Callable.hpp"
#include "kiwi/Overridable.hpp"

namespace kiwi
{
    //==--------------------------------------------------------------------==//
    /// Unary operator
    class UnaryOperator : public Callable, public Overridable<UnaryOperator> {
        friend class Type;
    public:
        /// create unary operator
        static UnaryPtr create(TypePtr ownerType, UnaryOpcode opcode, TypePtr returnType);

        /// returns binary operator opcode
        UnaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// returns result type
        TypePtr getReturnType() const {
            return m_returnType.lock();
        }

        /// classof check
        static bool classof(const MemberPtr type) {
            return type->getMemberID() == UnaryID;
        }

        /// classof check
        static bool classof(const UnaryPtr) {
            return true;
        }
    protected:
        UnaryOpcode             m_opcode;

        /// constructor
        UnaryOperator(UnaryOpcode opcode, TypePtr ownerType, TypePtr returnType);
    };

    //==--------------------------------------------------------------------==//
    /// Binary operator
    class BinaryOperator : public Callable, public Overridable<BinaryOperator> {
        friend class Type;
    public:
        /// create binary operator
        static BinaryPtr create(TypePtr ownerType, BinaryOpcode opcode, TypePtr returnType, TypePtr operandType);

        /// returns binary opcode
        BinaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// classof check
        static bool classof(const MemberPtr type) {
            return type->getMemberID() == BinaryID;
        }

        /// classof check
        static bool classof(const BinaryPtr) {
            return true;
        }
    protected:
        BinaryOpcode m_opcode;

        /// constructor
        BinaryOperator(BinaryOpcode opcode, TypePtr ownerType, TypePtr returnType);
    };

    //==--------------------------------------------------------------------==//
    /// Method argument
    class MultiaryOperator : public Callable, public Overridable<MultiaryOperator> {
        friend class Type;
    public:
        /// create multiary operator
        static MultiaryPtr create(TypePtr ownerType, MultiaryOpcode opcode, TypePtr returnType, TypeVector types);

        /// returns multiary opcode
        MultiaryOpcode getOpcode() const {
            return m_opcode;
        }
                /// classof check
        static bool classof(const MemberPtr type) {
            return type->getMemberID() == MultiaryID;
        }

        /// classof check
        static bool classof(const MultiaryPtr) {
            return true;
        }
    protected:
        MultiaryOpcode            m_opcode;

        /// constructor
        MultiaryOperator(MultiaryOpcode opcode, TypePtr ownerType, TypePtr returnType);
    };

    //==--------------------------------------------------------------------==//
    /// Method member
    class Method : public Callable, public Overridable<Method> {
        friend class Type;
        template<class Method> friend class MemberSet;
    public:
        /// Create method add register in type
        static MethodPtr create(TypePtr ownerType, TypePtr returnType, std::vector<TypePtr> arguments, const Identifier& name = "");

        /// Returns method name
        Identifier getName() const {
            return m_name;
        }

        /// classof check
        static bool classof(const MemberPtr type) {
            return type->getMemberID() == MethodID;
        }

        /// classof check
        static bool classof(const MethodPtr) {
            return true;
        }
    protected:
        Identifier m_name;

        /// constructor
        Method(const Identifier& name, TypePtr ownerType, TypePtr returnType);

        /// constructor for inhertit method
        Method(TypePtr ownerType, MethodPtr method);

        /// inherit member from base type
        static MethodPtr inherit(TypePtr ownerType, MethodPtr method);
    };

    //==--------------------------------------------------------------------==//
    /// Field member
    class Field : public Member, public Overridable<Field> {
        friend class Type;
        friend class ObjectType;
        template<class Field> friend class MemberSet;
    public:
        /// create field
        static FieldPtr create(TypePtr ownerType, TypePtr fieldType, const Identifier& name = "");

        /// returns field name
        Identifier getName() const {
            return m_name;
        }

        /// returns field type
        TypePtr getFieldType() const {
            return m_fieldType.lock();
        }

        /// returns position in address map
        int32_t getPosition() const {
            return m_position;
        }

        /// classof check
        static bool classof(const MemberPtr type) {
            return type->getMemberID() == FieldID;
        }

        /// classof check
        static bool classof(const FieldPtr) {
            return true;
        }
    protected:
        /// field name
        Identifier m_name;

        /// field type
        TypeWeak m_fieldType;

        /// field position in address map for class
        int32_t m_position;

        /// constructor: inherit field field
        Field(TypePtr ownerType, FieldPtr field);

        /// constructor: declare field field
        Field(TypePtr ownerType, TypePtr fieldType);

        /// constructor: declare anonym field
        Field(const Identifier& name, TypePtr ownerType, TypePtr fieldType);

        /// Set position
        void setPosition(int32_t position) {
            m_position = position;
        }

        /// Set name
        void setName(const Identifier& name) {
            m_name = name;
        }
        /// inherit field from base type
        static FieldPtr inherit(TypePtr ownerType, FieldPtr field);
    };
}

#endif
