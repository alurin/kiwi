/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_DERIVEDTYPES_INCLUDED
#define KIWI_DERIVEDTYPES_INCLUDED

#include "kiwi/Type.hpp"

namespace kiwi {
    //==--------------------------------------------------------------------==//
    /// Void types metadata
    class VoidType : public Type {
        friend class Context;
    public:
        /// returns void type from context
        static VoidPtr get(ContextPtr context);

        /// classof check
        static bool classof(const TypePtr type) {
            return type->getTypeID() == VoidID;
        }

        /// classof check
        static bool classof(const VoidPtr) {
            return true;
        }
    private:
        /// constructor
        VoidType(ModulePtr module);

        /// create integer type
        static VoidPtr create(ModulePtr module);
    };

    //==--------------------------------------------------------------------==//
    /// Integers types metadata
    class IntegerType : public Type
    {
        friend class Context;
    public:
        /// returns 32-bit signed integer type for context
        static IntegerPtr get32(ContextPtr context);

        /// classof check
        static bool classof(const TypePtr type) {
            return type->getTypeID() == IntID;
        }

        /// classof check
        static bool classof(const IntegerPtr) {
            return true;
        }
    private:
        /// constructor
        IntegerType(ModulePtr module, int32_t size, bool unsign);

        /// create integer type
        static IntegerPtr create(ModulePtr module, int32_t size, bool unsign);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// Boolean type metadata
    class BooleanType : public Type
    {
        friend class Context;
    public:
        /// returns boolean type from context
        static BooleanPtr get(ContextPtr context);

        /// classof check
        static bool classof(const TypePtr type) {
            return type->getTypeID() == BoolID;
        }

        /// classof check
        static bool classof(const BooleanPtr) {
            return true;
        }
    protected:
        /// constructor
        BooleanType(ModulePtr module);

        /// create module type
        static BooleanPtr create(ModulePtr module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// Character type metadata
    class CharType : public Type {
        friend class Context;
    public:
        /// return unicode character type from context
        static CharPtr get(ContextPtr context);

        /// classof check
        static bool classof(const TypePtr type) {
            return type->getTypeID() == CharID;
        }

        /// classof check
        static bool classof(const CharPtr) {
            return true;
        }
    protected:
        /// constructor
        CharType(ModulePtr module);

        /// create module type
        static CharPtr create(ModulePtr module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// String type metdata
    class StringType : public Type {
        friend class Context;
    public:
        /// returns unicode string type from context
        static StringPtr get(ContextPtr context);

        /// classof check
        static bool classof(const TypePtr type) {
            return type->getTypeID() == StringID;
        }

        /// classof check
        static bool classof(const StringPtr) {
            return true;
        }
    protected:
        /// constructor
        StringType(ModulePtr module);

        /// create module type
        static StringPtr create(ModulePtr module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// Interfaces metadata
    class InterfaceType : public Type {
    public:
        /// Inherti other interface
        void inherit(InterfacePtr type);

        /// classof check
        static bool classof(const TypePtr type) {
            return type->getTypeID() == InterfaceID;
        }

        /// classof check
        static bool classof(const InterfacePtr) {
            return true;
        }
    protected:
        // anonym object constructor
        InterfaceType(ModulePtr module);

        // constructor
        InterfaceType(ModulePtr module, const Identifier& name);
    };

    //==--------------------------------------------------------------------==//
    /// Object type
    class ObjectType : public Type {
    public:
        /// Create anonym object type in module
        static ObjectPtr create(ModulePtr module);

        /// Create object type in module
        static ObjectPtr create(ModulePtr module, const Identifier& name);

        /// Implement interface
        // void implement(InterfacePtr type);

        /// Inherit class
        bool inherit(ObjectPtr type);

        /// This class implement interface?
        bool isImplement(const InterfacePtr type, bool duckCast = true) const;

        /// This class inherits from class?
        bool isInherit(const ObjectPtr type) const;

        /// classof check
        static bool classof(const TypePtr type) {
            return type->getTypeID() == ObjectID;
        }

        /// classof check
        static bool classof(const ObjectPtr) {
            return true;
        }

        /// emit LLVM analog for type
        virtual void emit();
    protected:

        // anonym object constructor
        ObjectType(ModulePtr module);

        // constructor
        ObjectType(ModulePtr module, const Identifier& name);
    };
}

#endif
