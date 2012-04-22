#ifndef KIWI_DERIVEDTYPES_INCLUDED
#define KIWI_DERIVEDTYPES_INCLUDED

#include "kiwi/Type.hpp"

namespace kiwi
{
    typedef boost::shared_ptr<class VoidType>      VoidTy;
    typedef boost::shared_ptr<class IntType>       IntTy;
    typedef boost::shared_ptr<class BoolType>      BoolTy;
    typedef boost::shared_ptr<class CharType>      CharTy;
    typedef boost::shared_ptr<class StringType>    StringTy;
    typedef boost::shared_ptr<class InterfaceType> InterfaceTy;
    typedef boost::shared_ptr<class ObjectType>    ObjectTy;


    //==--------------------------------------------------------------------==//
    /// Void types metadata
    class VoidType : public Type {
        friend class Context;
    public:
        static VoidTy get(ContextRef context);
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
        static IntTy get32(ContextRef context);
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
        static BoolTy get(ContextRef context);
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
        static CharTy get(ContextRef context);
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
        static StringTy get(ContextRef context);
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
        /// Create anonym object type
        static ObjectTy create(const ModuleRef& module);

        /// Create object type
        static ObjectTy create(const ModuleRef& module, const Identifier& name);

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
