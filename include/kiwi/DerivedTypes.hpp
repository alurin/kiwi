#ifndef KIWI_DERIVEDTYPES_INCLUDED
#define KIWI_DERIVEDTYPES_INCLUDED

#include "kiwi/Type.hpp"

namespace kiwi
{
    /// Void types metadata
    class VoidType : public Type {
        friend class Context;
    public:
        static TypeRef get(ContextRef context);

    private:
        /// constructor
        VoidType(ModuleRef module);

        /// create integer type
        static TypeRef create(ModuleRef module);
    };

    /// Integers types metadata
    class IntType : public Type
    {
        friend class Context;
    public:
        static TypeRef get32(ContextRef context);
    private:
        /// constructor
        IntType(ModuleRef module, int32_t size, bool unsign);

        /// create integer type
        static TypeRef create(ModuleRef module, int32_t size, bool unsign);

        /// initializator
        void initializate();
    };

    /// Boolean type metadata
    class BoolType : public Type
    {
        friend class Context;
    public:
        static TypeRef get(ContextRef context);
    protected:
        /// constructor
        BoolType(ModuleRef module);

        /// create module type
        static TypeRef create(ModuleRef module);

        /// initializator
        void initializate();
    };

    /// Character type metadata
    class CharType : public Type {
        friend class Context;
    public:
        static TypeRef get(ContextRef context);
    protected:
        /// constructor
        CharType(ModuleRef module);

        /// create module type
        static TypeRef create(ModuleRef module);

        /// initializator
        void initializate();
    };

    /// String type metdata
    class StringType : public Type {
        friend class Context;
    public:
        static TypeRef get(ContextRef context);
    protected:
        /// constructor
        StringType(ModuleRef module);

        /// create module type
        static TypeRef create(ModuleRef module);

        /// initializator
        void initializate();
    };

}

#endif
