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
    class TypeImpl;

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

        TypeImpl* getMetadata() const {
            return m_meta;
        }

        /// return LLVM analog for variables
        llvm::Type* getVarType() const;

        /// add unary operator
        UnaryOperator* addUnary(
            Member::UnaryOpcode opcode,
            Type* returnType,
            codegen::CallableEmitter* emitter
        );

        /// add binary operator
        BinaryOperator* addBinary(
            Member::BinaryOpcode opcode,
            Type* returnType,
            Type* operandType,
            codegen::CallableEmitter* emitter
        );

        /// add binary operator
        MultiaryOperator* addMultiary(
            Member::MultiaryOpcode opcode,
            Type* returnType,
            std::vector<Type*> arguments,
            codegen::CallableEmitter* emitter
        );

        /// add field
        Field* addField(const Identifier& name, Type* type);

        /// Merge inherited field
        Field* mergeField(Field* declared, Field* inherited);

        /// find field operator
        Field* findField(const Identifier& name) const;

        /// add method
        Method* addMethod(const Identifier& name, Type* returnType, std::vector<Type*> arguments);

        /// find unary operator
        UnaryOperator* findUnary(Member::UnaryOpcode opcode) const;

        /// find binary operator
        BinaryOperator* findBinary(Member::BinaryOpcode opcode, Type* operandType) const;

        /// find binary operator
        MultiaryOperator* findMultiary(Member::MultiaryOpcode opcode, std::vector<Type*> arguments) const;

        /// find method
        Method* findMethod(const Identifier& name, std::vector<Type*> arguments) const;

        /// find cast operator
        virtual CastOperator* findCastTo(const Type* type) const;

        //==--------------------------------------------------------------------------------------------------------==//
        //          Method for work with type system
        //==--------------------------------------------------------------------------------------------------------==//
        /// This class inherits from type?
        virtual bool isInherit(const Type* type, bool duckCast = false) const;

        /// Type is castable to other type (up-cast(from child to parent) or implict cast)
        virtual bool isCastableTo(const Type* type, bool duckCast = true) const;

        /// emit type metadata and structure
        virtual void emit();

        /// returns name of type
        Identifier getName() const {
            return m_name;
        }
    protected:
        /// Internal storage for type parameters
        TypeImpl* m_meta;

        /// Class uniqual identifier
        TypeID m_typeID;

        /// Type module
        Module* m_module;

        /// Name of type
        Identifier m_name;

        /// constructor
        Type(Module* module);

        /// add base type
        void inheritBase(Type* type);
    };
}

#endif
