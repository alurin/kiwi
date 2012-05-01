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
        /// returns binary operator opcode
        UnaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// returns result type
        Type* getReturnType() const {
            return m_returnType;
        }

        /// classof check
        static bool classof(const Member* type) {
            return type->getMemberID() == UnaryID;
        }

        /// classof check
        static bool classof(const UnaryOperator*) {
            return true;
        }
    protected:
        UnaryOpcode             m_opcode;

        /// constructor
        UnaryOperator(
            UnaryOpcode opcode,
            Type* ownerType,
            Type* returnType
        );
    };

    //==--------------------------------------------------------------------==//
    /// Binary operator
    class BinaryOperator : public Callable, public Overridable<BinaryOperator> {
        friend class Type;
    public:
        /// returns binary opcode
        BinaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// classof check
        static bool classof(const Member* type) {
            return type->getMemberID() == BinaryID;
        }

        /// classof check
        static bool classof(const BinaryOperator*) {
            return true;
        }
    protected:
        BinaryOpcode m_opcode;

        /// constructor
        BinaryOperator(
            BinaryOpcode opcode,
            Type* ownerType,
            Type* returnType,
            Type* operandType
        );
    };

    //==--------------------------------------------------------------------==//
    /// Method argument
    class MultiaryOperator : public Callable, public Overridable<MultiaryOperator> {
        friend class Type;
    public:
        /// returns multiary opcode
        MultiaryOpcode getOpcode() const {
            return m_opcode;
        }
                /// classof check
        static bool classof(const Member* type) {
            return type->getMemberID() == MultiaryID;
        }

        /// classof check
        static bool classof(const MultiaryOperator*) {
            return true;
        }
    protected:
        MultiaryOpcode            m_opcode;

        // constructor
        MultiaryOperator(
            MultiaryOpcode opcode,
            Type* ownerType,
            Type* returnType,
            TypeVector types
        );
    };

    //==--------------------------------------------------------------------==//
    /// Method member
    class Method : public Callable, public Overridable<Method> {
        friend class Type;
        template<class Method> friend class MemberSet;
    public:
        /// Returns method name
        Identifier getName() const {
            return m_name;
        }

        /// returns this is static method?
        bool isStatic() const {
            return false;
        }

        /// returns this is abstract method?
        bool isAbstract() const {
            return false;
        }

        /// classof check
        static bool classof(const Member* type) {
            return type->getMemberID() == MethodID;
        }

        /// classof check
        static bool classof(const Method*) {
            return true;
        }
    protected:
        Identifier m_name;

        /// constructor for inhertit method
        Method(Type* ownerType, Method* method);

        /// constructor
        Method(const Identifier& name, Type* ownerType, Type* returnType, std::vector<Type*> arguments);
    };

    //==--------------------------------------------------------------------==//
    /// Field member
    class Field : public Member, public Overridable<Field> {
        friend class Type;
        friend class ObjectType;
        template<class Field> friend class MemberSet;
    public:
        /// returns field name
        Identifier getName() const {
            return m_name;
        }

        /// returns field type
        Type* getFieldType() const {
            return m_fieldType;
        }

        /// returns position in address map
        int32_t getPosition() const {
            return m_position;
        }

        /// classof check
        static bool classof(const Member* type) {
            return type->getMemberID() == FieldID;
        }

        /// classof check
        static bool classof(const Field*) {
            return true;
        }
    protected:
        /// field name
        Identifier m_name;

        /// field type
        Type* m_fieldType;

        /// field position in address map for class
        int32_t m_position;

        /// constructor: inherit field field
        Field(Type* ownerType, Field* field);

        /// constructor: declare field field
        Field(Type* ownerType, Type* fieldType);

        /// constructor: declare anonym field
        Field(const Identifier& name, Type* ownerType, Type* fieldType);

        /// Set position
        void setPosition(int32_t position) {
            m_position = position;
        }

        /// Set name
        void setName(const Identifier& name) {
            m_name = name;
        }
    };

    //==--------------------------------------------------------------------==//
    /// Cast operator
    class CastOperator : public Callable, public Overridable<CastOperator> {
        friend class Type;
    protected:
        /// constructor
        CastOperator(Type* sourceType, Type* destType);
    };
}

#endif
