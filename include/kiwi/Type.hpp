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
        ContextPtr getContext() const;

        /// returns type owner module
        ModulePtr getModule() const {
            return m_module.lock();
        }

        TypeImpl* getMetadata() const {
            return m_meta;
        }

        /// return LLVM analog for variables
        llvm::Type* getVarType() const;

        /// add unary operator
        UnaryPtr addUnary(Member::UnaryOpcode opcode, TypePtr returnType);

        /// add binary operator
        BinaryPtr addBinary(Member::BinaryOpcode opcode, TypePtr returnType, TypePtr operandType);

        /// add binary operator
        MultiaryPtr addMultiary(Member::MultiaryOpcode opcode, TypePtr returnType, std::vector<TypePtr> arguments);

        /// add field
        FieldPtr addField(const Identifier& name, TypePtr type);

        /// Merge inherited field
        void mergeField(FieldPtr declared, FieldPtr inherited);

        /// find field operator
        FieldPtr findField(const Identifier& name) const;

        /// add method
        MethodPtr addMethod(const Identifier& name, TypePtr returnType, std::vector<TypePtr> arguments);

        /// find unary operator
        UnaryPtr findUnary(Member::UnaryOpcode opcode) const;

        /// find binary operator
        BinaryPtr findBinary(Member::BinaryOpcode opcode, TypePtr operandType) const;

        /// find binary operator
        MultiaryPtr findMultiary(Member::MultiaryOpcode opcode, std::vector<TypePtr> arguments) const;

        /// find method
        MethodPtr findMethod(const Identifier& name, std::vector<TypePtr> arguments) const;

        //==--------------------------------------------------------------------------------------------------------==//
        //          Method for work with type system
        //==--------------------------------------------------------------------------------------------------------==//
        /// This class inherits from type?
        virtual bool isInherit(const TypePtr type, bool duckCast = false) const;

        /// Type is castable to other type (up-cast(from child to parent) or implict cast)
        virtual bool isCastableTo(const TypePtr type, bool duckCast = true) const;

        /// emit type metadata and structure
        virtual void emit();

        /// returns name of type
        Identifier getName() const {
            return m_name;
        }

        size_t field_size() const;

        /// dump information about type
        void dump();
    protected:
        /// Internal storage for type parameters
        TypeImpl* m_meta;

        /// Class uniqual identifier
        TypeID m_typeID;

        /// Type module
        ModuleWeak m_module;

        /// Name of type
        Identifier m_name;

        /// constructor
        Type(ModulePtr module);

        /// add base type
        void inheritBase(TypePtr type);
    };
}

#endif
