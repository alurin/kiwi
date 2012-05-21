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

    // Iterators
    class MemberIterator;
    class MethodIterator;
    class FieldIterator;
    class AncestorIterator;

    /// Type metadata
    class Type :
        public boost::enable_shared_from_this<Type>,
        public boost::noncopyable {
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

        /// returns internal metadata for type
        TypeImpl* getMetadata() const {
            return m_meta;
        }

        //==----------------------------------------------------------------==//
        //          Methods for work with type fields
        //==----------------------------------------------------------------==//

        /// add field
        FieldPtr addField(const Identifier& name, TypePtr type);

        /// Merge inherited field
        void mergeField(FieldPtr declared, FieldPtr inherited);

        /// find field operator
        FieldPtr findField(const Identifier& name) const;

        /// has type contains fields?
        bool hasFields() const;

        /// returns count of fields
        size_t getFieldsCount() const;

        //==----------------------------------------------------------------==//
        //          Methods for work with type methods
        //==----------------------------------------------------------------==//

        /// add unary operator
        /// @deprecated
        /// @see addMethod
        MethodPtr addUnary(Member::MethodOpcode opcode, TypePtr returnType);

        /// add binary operator
        /// @deprecated
        /// @see addMethod
        MethodPtr addBinary(
            Member::MethodOpcode opcode,
            TypePtr returnType,
            TypePtr operandType
        );

        /// add binary operator
        /// @deprecated
        /// @see addMethod
        MethodPtr addMultiary(
            Member::MethodOpcode opcode,
            TypePtr returnType,
            std::vector<TypePtr> arguments
        );

        /// add method
        MethodPtr addMethod(
           const Identifier& name,
           TypePtr returnType,
           std::vector<TypePtr> arguments
        );

        /// find unary operator
        /// @deprecated
        /// @see findMethod
        MethodPtr findUnary(Member::MethodOpcode opcode) const;

        /// find binary operator
        /// @deprecated
        /// @see findMethod
        MethodPtr findBinary(
            Member::MethodOpcode opcode,
            TypePtr operandType
        ) const;

        /// find binary operator
        /// @deprecated
        /// @see findMethod
        MethodPtr findMultiary(
            Member::MethodOpcode opcode,
            std::vector<TypePtr> arguments
        ) const;

        /// find method
        MethodPtr findMethod(
            const Identifier& name,
            std::vector<TypePtr> arguments
        ) const;

        /// find method
        MethodPtr findMethod(
            Member::MethodOpcode opcode,
            std::vector<TypePtr> arguments
        ) const;

        /// has type contains methods?
        bool hasMethods() const;

        /// returns count of methods
        size_t getMethodsCount() const;

        //==----------------------------------------------------------------==//
        //          Methods for work with type ancestors
        //==----------------------------------------------------------------==//

        /// find ancestor type
        AncestorPtr findAncestor(TypePtr ancestorType);

        /// find derived type
        AncestorPtr findDerived(TypePtr derivedType) {
            return derivedType->findAncestor(shared_from_this());
        }

        /// This type derived from other type?
        bool isAncestor(TypePtr type) const;

        /// This type is ancestor for other type?
        bool isDerived(TypePtr type) const {
            return type->isAncestor(TypePtr(shared_from_this(), const_cast<Type*>(this)));
        }

        /// has type contains ancestors?
        bool hasAncestors() const;

        /// returns count of ancestors
        size_t getAncestorsCount() const;

        //==----------------------------------------------------------------==//
        //          Runtime utilites for work with type system in runtime
        //==----------------------------------------------------------------==//

        /// return pointer to vtable
        void* getVTablePointer(TypePtr type = TypePtr());

        /// return pointer to amap
        void* getAMapPointer(TypePtr type = TypePtr());

        //==----------------------------------------------------------------==//
        //          Method for work with type system
        //==----------------------------------------------------------------==//

        /// Type is castable to other type by up-cast from derived to ancestor
        /// type or implict cast
        virtual bool isCastableTo(const TypePtr type, bool duckCast = true) const;

        /// emit type metadata and structure
        virtual void update();

        /// returns name of type
        Identifier getName() const {
            return m_name;
        }

        //==----------------------------------------------------------------==//
        //         Iterators over type elements
        //==----------------------------------------------------------------==//
        /// iterate over type members
        void each(MemberIterator& it);

        /// iterate over type methods
        void each(MethodIterator& it);

        /// iterate over
        void each(FieldIterator& it);

        /// iterate over
        void each(AncestorIterator& it);

        //==----------------------------------------------------------------==//
        //         Utils and debug methods
        //==----------------------------------------------------------------==//
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

        /// Add type ancestor
        bool addAncestor(TypePtr type);
    };
}

#endif
