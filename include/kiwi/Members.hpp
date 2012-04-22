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

        /// Returns method name
        Identifier getName() const {
            return m_name;
        }

        /// returns method result type
        TypeRef getResultType() const {
            return m_resultType.lock();
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
    protected:
        Identifier                  m_name;
        TypeWeak                    m_ownerType;
        TypeWeak                    m_resultType;
        std::vector<ArgumentRef>    m_arguments;
        llvm::Function*             m_func;

        Method(const Identifier& name, const TypeRef& ownerType, const TypeRef& resultType, std::vector<ArgumentRef> arguments);
    };

    /// Fields. Not implemented
    class Field : public Member {
        friend class Type;
    public:
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