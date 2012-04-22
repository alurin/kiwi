#ifndef KIWI_MEMBERS_INCLUDED
#define KIWI_MEMBERS_INCLUDED

#include "kiwi/Member.hpp"
#include <vector>

namespace kiwi
{
    class Argument;
    class Method;

    namespace codegen {
        class UnaryEmitter;
        class BinaryEmitter;
    };

    //==--------------------------------------------------------------------==//
    /// Unary operator
    class UnaryOperator : public Member {
        friend class Type;
    public:
        /// virtual destructor
        virtual ~UnaryOperator();

        /// returns binary operator opcode
        UnaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// returns result type
        Type* getResultType() const {
            return m_resultType;
        }

        /// returns IR code emitter
        codegen::UnaryEmitter* getEmitter() const {
            return m_emitter;
        }

        /// classof check
        static bool classof(class Member* type) {
            return type->getMemberID() == UnaryOperatorID;
        }

        /// classof check
        static bool classof(const UnaryOperator*) {
            return true;
        }
    protected:
        UnaryOpcode             m_opcode;
        Type*                m_resultType;
        codegen::UnaryEmitter*  m_emitter;

        /// constructor
        UnaryOperator(
            UnaryOpcode opcode,
            Type* ownerType,
            Type* resultType,
            codegen::UnaryEmitter* emitter
        );
    };

    //==--------------------------------------------------------------------==//
    /// Binary operator
    class BinaryOperator : public Member {
        friend class Type;
    public:
        /// virtual destructor
        virtual ~BinaryOperator();

        /// returns binary opcode
        BinaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// return result type
        /// @nostable
        Type* getResultType() const {
            return m_resultType;
        }

        /// return second operator type
        /// @nostable
        Type* getOperandType() const {
            return m_operandType;
        }

        /// return IR code emitter
        codegen::BinaryEmitter* getEmitter() const {
            return m_emitter;
        }

        /// classof check
        static bool classof(class Member* type) {
            return type->getMemberID() == BinaryOperatorID;
        }

        /// classof check
        static bool classof(const BinaryOperator&) {
            return true;
        }
    protected:
        BinaryOpcode             m_opcode;
        Type*                 m_resultType;
        Type*                 m_operandType;
        codegen::BinaryEmitter*  m_emitter;

        /// constructor
        BinaryOperator(
            BinaryOpcode opcode,
            Type* ownerType,
            Type* resultType,
            Type* operandType,
            codegen::BinaryEmitter* emitter
        );
    };

    //==--------------------------------------------------------------------==//
    /// Method argument
    class Argument {
        friend class Method;
    public:
        /// return argument owner
        Method* getOwner() const {
            return m_owner;
        }

        /// returns argument name
        Identifier getName() const {
            return m_name;
        }

        /// set argument name
        void setName(const Identifier& name) {
            m_name = name;
        }

        /// returns argument type
        Type* getType () const {
            return m_type;
        }

        /// returns argument position
        int32_t getPosition() const {
            return m_position;
        }
    protected:
        /// argument owner method
        Method* m_owner;

        /// argument name
        Identifier m_name;

        /// argument type
        Type* m_type;

        /// argument position
        int32_t m_position;

        Argument(Method* owner, Type* type, int32_t position);
    };

    //==--------------------------------------------------------------------==//
    /// Methods
    class Method : public Member {
        friend class Type;
    public:
        typedef std::vector<Argument*>::const_iterator const_iterator;

        /// virtual destructor
        virtual ~Method();

        /// Returns method name
        Identifier getName() const {
            return m_name;
        }

        /// returns method result type
        Type* getResultType() const {
            return m_resultType;
        }

        /// returns this is static method?
        bool isStatic() const {
            return m_isStatic;
        }

        /// returns llvm analog
        llvm::Function* getFunction() const {
            return m_func;
        }

        /// set llvm analog
        void setFunction(llvm::Function* func) {
            m_func = func;
        }

        /// returns first argument (iterator)
        const_iterator begin() const { return m_arguments.begin(); }
        /// returns last argument (iterator)
        const_iterator end()   const { return m_arguments.end();   }

        /// classof check
        static bool classof(class Member* type) {
            return type->getMemberID() == MethodID;
        }

        /// classof check
        static bool classof(const Method*) {
            return true;
        }
    protected:
        Identifier m_name;
        Type* m_ownerType;
        Type* m_resultType;
        std::vector<Argument*> m_arguments;
        llvm::Function* m_func;
        bool m_isStatic;

        Method(const Identifier& name, Type* ownerType, Type* resultType, std::vector<Type*> arguments);
    };

    //==--------------------------------------------------------------------==//
    /// Fields. Not implemented
    class Field : public Member {
        friend class Type;
        friend class ObjectType;
    public:
        /// virtual destructor
        virtual ~Field();

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
        static bool classof(class Member* type) {
            return type->getMemberID() == FieldID;
        }

        /// classof check
        static bool classof(const Field*) {
            return true;
        }
    protected:
        Identifier  m_name;
        Type*    m_fieldType;
        int32_t     m_position;

        /// constructor
        Field(const Identifier& name, Type* ownerType, Type* fieldType);

        /// Set position
        void setPosition(int32_t position) {
            m_position = position;
        }
    };
}

#endif
