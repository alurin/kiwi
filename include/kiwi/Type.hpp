/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_TYPE_INCLUDED
#define KIWI_TYPE_INCLUDED

#include "kiwi/Member.hpp"
#include <vector>

namespace llvm {
    class Type;
}

namespace kiwi {
    namespace codegen {
        class UnaryEmitter;
        class BinaryEmitter;
        class CallableEmitter;
    };
    class Context;
    class Module;
    class Member;
    class Type;
    class BinaryOperator;
    class UnaryOperator;
    class MultiaryOperator;
    class Method;
    class Field;
    class CastOperator;

    /// Type metadata
    class Type {
        Type(const Type&);                   ///< NOT IMPLEMENT!!!
        Type& operator=(const Type& type);   ///< NOT IMPLEMENT!!!
    public:
        /// Type identifier
        enum TypeID {
            VoidID = 1,
            IntID,
            BoolID,
            CharID,
            StringID,
            ObjectID,
            InterfaceID
        };

        /// destructor
        virtual ~Type();

        /// returns type identifier
        TypeID getTypeID() const {
            return m_typeID;
        }

        /// returns type owner context
        Context* getContext() const;

        /// returns type owner module
        Module* getModule() const {
            return m_module;
        }

        /// return LLVM analog for variables
        llvm::Type* getVarType() const {
            return m_varType;
        }

        /// add unary operator
        UnaryOperator* addUnary(
            Member::UnaryOpcode opcode,
            Type* resultType,
            codegen::UnaryEmitter* emitter
        );

        /// add binary operator
        BinaryOperator* addBinary(
            Member::BinaryOpcode opcode,
            Type* resultType,
            Type* operandType,
            codegen::BinaryEmitter* emitter
        );

        /// add binary operator
        MultiaryOperator* addMultiary(
            Member::MultiaryOpcode opcode,
            Type* resultType,
            std::vector<Type*> arguments,
            codegen::CallableEmitter* emitter
        );

        /// add field
        Field* addField(const Identifier& name, Type* type);

        /// add method
        Method* addMethod(const Identifier& name, Type* resultType, std::vector<Type*> arguments);

        /// find unary operator
        UnaryOperator* findUnary(Member::UnaryOpcode opcode) const;

        /// find binary operator
        BinaryOperator* findBinary(Member::BinaryOpcode opcode, Type* operandType) const;

        /// find binary operator
        MultiaryOperator* findMultiary(Member::MultiaryOpcode opcode, std::vector<Type*> arguments) const;

        /// find field operator
        Field* findField(const Identifier& name) const;

        /// find method
        Method* findMethod(const Identifier& name, std::vector<Type*> arguments) const;

        /// find cast operator
        virtual CastOperator* findCastTo(const Type* type) const;

        /// Type is castable to other type (up-cast(from child to parent) or implict cast)
        virtual bool isCastableTo(const Type* type, bool duckCast = true) const;

        /// emit type metadata and structure
        virtual void emit();

        /// returns name of type
        Identifier getName() const {
            return m_name;
        }
    protected:
        /// Class uniqual identifier
        TypeID m_typeID;

        /// Type module
        Module* m_module;

        /// Name of type
        Identifier m_name;

        /// List of unary operators
        std::vector<UnaryOperator*> m_unary;

        /// List of binary operators
        std::vector<BinaryOperator*> m_binary;

        /// List of multiary operators
        std::vector<MultiaryOperator*> m_multiary;

        /// List of methods
        std::vector<Method*> m_methods;

        /// List of fields
        std::vector<Field*> m_fields;

        /// LLVM analog
        llvm::Type* m_varType;

        /// constructor
        Type(Module* module);
    };
}

#endif
