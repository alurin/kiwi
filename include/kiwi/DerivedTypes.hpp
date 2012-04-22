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
        VoidType(ModuleRef module);

        /// create integer type
        static VoidTy create(ModuleRef module);
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
        IntType(ModuleRef module, int32_t size, bool unsign);

        /// create integer type
        static IntTy create(ModuleRef module, int32_t size, bool unsign);

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
        BoolType(ModuleRef module);

        /// create module type
        static BoolTy create(ModuleRef module);

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
        CharType(ModuleRef module);

        /// create module type
        static CharTy create(ModuleRef module);

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
        StringType(ModuleRef module);

        /// create module type
        static StringTy create(ModuleRef module);

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
        /// Create object type
        static ObjectTy create(const ModuleRef& module, const Identifier& name);

        // void inherit(ObjectTy type);
        // AddressMap      getAddressMap() const;
        // VirtualTable    getVirtualTable() const;
    protected:
    };
}

#endif
