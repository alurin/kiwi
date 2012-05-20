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

namespace kiwi {
    class TypeImpl;

    /// Type metadata
    class Type : public boost::enable_shared_from_this<Type>, public boost::noncopyable {
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

        /// add unary operator
        /// @deprecated
        /// @see addMethod
        MethodPtr addUnary(Member::MethodOpcode opcode, TypePtr returnType);

        /// add binary operator
        /// @deprecated
        /// @see addMethod
        MethodPtr addBinary(Member::MethodOpcode opcode, TypePtr returnType, TypePtr operandType);

        /// add binary operator
        /// @deprecated
        /// @see addMethod
        MethodPtr addMultiary(Member::MethodOpcode opcode, TypePtr returnType, std::vector<TypePtr> arguments);

        /// add field
        FieldPtr addField(const Identifier& name, TypePtr type);

        /// Merge inherited field
        void mergeField(FieldPtr declared, FieldPtr inherited);

        /// find field operator
        FieldPtr findField(const Identifier& name) const;

        /// add method
        MethodPtr addMethod(const Identifier& name, TypePtr returnType, std::vector<TypePtr> arguments);

        /// find unary operator
        /// @deprecated
        /// @see findMethod
        MethodPtr findUnary(Member::MethodOpcode opcode) const;

        /// find binary operator
        /// @deprecated
        /// @see findMethod
        MethodPtr findBinary(Member::MethodOpcode opcode, TypePtr operandType) const;

        /// find binary operator
        /// @deprecated
        /// @see findMethod
        MethodPtr findMultiary(Member::MethodOpcode opcode, std::vector<TypePtr> arguments) const;

        /// find method
        MethodPtr findMethod(const Identifier& name, std::vector<TypePtr> arguments) const;

        /// find method
        MethodPtr findMethod(Member::MethodOpcode opcode, std::vector<TypePtr> arguments) const;

        //==--------------------------------------------------------------------------------------------------------==//
        //          Method for work with type system in runtime
        //==--------------------------------------------------------------------------------------------------------==//
        /// return pointer to vtable
        void* getVTablePointer(TypePtr type = TypePtr());

        /// return pointer to amap
        void* getAMapPointer(TypePtr type = TypePtr());

        //==--------------------------------------------------------------------------------------------------------==//
        //          Method for work with type system
        //==--------------------------------------------------------------------------------------------------------==//
        /// This class inherits from type?
        virtual bool isInherit(const TypePtr type, bool duckCast = false) const;

        /// Type is castable to other type (up-cast(from child to parent) or implict cast)
        virtual bool isCastableTo(const TypePtr type, bool duckCast = true) const;

        /// emit type metadata and structure
        virtual void update();

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
