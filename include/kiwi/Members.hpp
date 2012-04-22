#ifndef KIWI_MEMBERS_INCLUDED
#define KIWI_MEMBERS_INCLUDED

#include "kiwi/Member.hpp"
#include <vector>

namespace kiwi
{
    typedef boost::shared_ptr<class Argument> ArgumentRef;

    namespace codegen
    {
        class UnaryEmitter;
        class BinaryEmitter;
    };

    /// Unary operator
    class UnaryOperator : public Member
    {
        friend class Type;
    public:
        /// virtual destructor
        virtual ~UnaryOperator();

        /// returns binary operator opcode
        UnaryOpcode getOpcode() const {
            return m_opcode;
        }

        /// returns result type
        TypeRef getResultType() const {
            return m_resultType.lock();
        }

        /// returns IR code emitter
        codegen::UnaryEmitter* getEmitter() const {
            return m_emitter;
        }

        /// classof check
        static bool classof(const MemberRef& type) {
            return type->getMemberID() == UnaryOperatorID;
        }

        /// classof check
        static bool classof(const UnaryRef&) {
            return true;
        }
    protected:
        UnaryOpcode             m_opcode;
        TypeWeak                m_resultType;
        codegen::UnaryEmitter*  m_emitter;

        /// constructor
        UnaryOperator(
            UnaryOpcode opcode,
            const TypeRef& ownerType,
            const TypeRef& resultType,
            codegen::UnaryEmitter* emitter
        );
    };

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
        TypeRef getResultType() const {
            return m_resultType.lock();
        }

        /// return second operator type
        /// @nostable
        TypeRef getOperandType() const {
            return m_operandType.lock();
        }

        /// return IR code emitter
        codegen::BinaryEmitter* getEmitter() const {
            return m_emitter;
        }

        /// classof check
        static bool classof(const MemberRef& type) {
            return type->getMemberID() == BinaryOperatorID;
        }

        /// classof check
        static bool classof(const BinaryRef&) {
            return true;
        }
    protected:
        BinaryOpcode             m_opcode;
        TypeWeak                 m_resultType;
        TypeWeak                 m_operandType;
        codegen::BinaryEmitter*  m_emitter;

        /// constructor
        BinaryOperator(
            BinaryOpcode opcode,
            const TypeRef& ownerType,
            const TypeRef& resultType,
            const TypeRef& operandType,
            codegen::BinaryEmitter* emitter
        );
    };

    /// Method argument
    class Argument {
    public:
        static ArgumentRef create(const Identifier& name, const TypeRef& type);

        Identifier getName() const {
            return m_name;
        }

        TypeRef getType () const {
            return m_type.lock();
        }
    protected:
        Identifier  m_name;
        TypeWeak    m_type;

        Argument(const Identifier& name, const TypeRef& type);
    };

    /// Methods
    class Method : public Member {
        friend class Type;
    public:
        typedef std::vector<ArgumentRef>::const_iterator const_iterator;

        /// virtual destructor
        virtual ~Method();

        /// Returns method name
        Identifier getName() const {
            return m_name;
        }

        /// returns method result type
        TypeRef getResultType() const {
            return m_resultType.lock();
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
        static bool classof(const MemberRef& type) {
            return type->getMemberID() == MethodID;
        }

        /// classof check
        static bool classof(const MethodRef&) {
            return true;
        }
    protected:
        Identifier                  m_name;
        TypeWeak                    m_ownerType;
        TypeWeak                    m_resultType;
        std::vector<ArgumentRef>    m_arguments;
        llvm::Function*             m_func;
        bool                        m_isStatic;

        Method(const Identifier& name, const TypeRef& ownerType, const TypeRef& resultType, std::vector<ArgumentRef> arguments);
    };

    /// Fields. Not implemented
    class Field : public Member {
        friend class Type;
    public:
        /// virtual destructor
        virtual ~Field();

        /// returns field name
        Identifier getName() const {
            return m_name;
        }

        /// returns field type
        TypeRef getFieldType() const {
            return m_fieldType.lock();
        }

        /// returns position in address map
        int32_t getPosition() const {
            return m_position;
        }

        /// classof check
        static bool classof(const MemberRef& type) {
            return type->getMemberID() == FieldID;
        }

        /// classof check
        static bool classof(const FieldRef&) {
            return true;
        }
    protected:
        Identifier  m_name;
        TypeWeak    m_fieldType;
        int32_t     m_position;

        /// constructor
        Field(const Identifier& name, const TypeRef& ownerType, const TypeRef& fieldType);

        ///
        void setPosition(int32_t position) {
            m_position = position;
        }
    };
}

#endif