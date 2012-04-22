#ifndef KIWI_DERIVEDTYPES_INCLUDED
#define KIWI_DERIVEDTYPES_INCLUDED

#include "kiwi/Type.hpp"

namespace kiwi
{
    //==--------------------------------------------------------------------==//
    /// Void types metadata
    class VoidType : public Type {
        friend class Context;
    public:
        /// returns void type from context
        static VoidTy get(const ContextRef& context);

        /// classof check
        static bool classof(const TypeRef& type) {
            return type->getTypeID() == VoidID;
        }

        /// classof check
        static bool classof(const VoidTy&) {
            return true;
        }
    private:
        /// constructor
        VoidType(const ModuleRef& module);

        /// create integer type
        static VoidTy create(const ModuleRef& module);
    };

    //==--------------------------------------------------------------------==//
    /// Integers types metadata
    class IntType : public Type
    {
        friend class Context;
    public:
        /// returns 32-bit signed integer type for context
        static IntTy get32(const ContextRef& context);

        /// classof check
        static bool classof(const TypeRef& type) {
            return type->getTypeID() == IntID;
        }

        /// classof check
        static bool classof(const IntTy&) {
            return true;
        }
    private:
        /// constructor
        IntType(const ModuleRef& module, int32_t size, bool unsign);

        /// create integer type
        static IntTy create(const ModuleRef& module, int32_t size, bool unsign);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// Boolean type metadata
    class BoolType : public Type
    {
        friend class Context;
    public:
        /// returns boolean type from context
        static BoolTy get(const ContextRef& context);

        /// classof check
        static bool classof(const TypeRef& type) {
            return type->getTypeID() == BoolID;
        }

        /// classof check
        static bool classof(const BoolTy&) {
            return true;
        }
    protected:
        /// constructor
        BoolType(const ModuleRef& module);

        /// create module type
        static BoolTy create(const ModuleRef& module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// Character type metadata
    class CharType : public Type {
        friend class Context;
    public:
        /// return unicode character type from context
        static CharTy get(const ContextRef& context);

        /// classof check
        static bool classof(const TypeRef& type) {
            return type->getTypeID() == CharID;
        }

        /// classof check
        static bool classof(const CharTy&) {
            return true;
        }
    protected:
        /// constructor
        CharType(const ModuleRef& module);

        /// create module type
        static CharTy create(const ModuleRef& module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    /// String type metdata
    class StringType : public Type {
        friend class Context;
    public:
        /// returns unicode string type from context
        static StringTy get(const ContextRef& context);

        /// classof check
        static bool classof(const TypeRef& type) {
            return type->getTypeID() == StringID;
        }

        /// classof check
        static bool classof(const StringTy&) {
            return true;
        }
    protected:
        /// constructor
        StringType(const ModuleRef& module);

        /// create module type
        static StringTy create(const ModuleRef& module);

        /// initializator
        void initializate();
    };

    //==--------------------------------------------------------------------==//
    class InterfaceType : public Type {

    };

    //==--------------------------------------------------------------------==//
    /// Object type
    class ObjectType : public Type {
    public:
        /// Create anonym object type in module
        static ObjectTy create(const ModuleRef& module);

        /// Create object type in module
        static ObjectTy create(const ModuleRef& module, const Identifier& name);

        /// classof check
        static bool classof(const TypeRef& type) {
            return type->getTypeID() == ObjectID;
        }

        /// classof check
        static bool classof(const ObjectTy&) {
            return true;
        }

        // void inherit(ObjectTy type);
        // AddressMap      getAddressMap() const;
        // VirtualTable    getVirtualTable() const;
    protected:
        // anonym object constructor
        ObjectType(const ModuleRef& module);

        // constructor
        ObjectType(const ModuleRef& module, const Identifier& name);
    };
}

#endif
