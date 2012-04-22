#ifndef KIWI_CONTEXTMETA_INTERNAL
#define KIWI_CONTEXTMETA_INTERNAL

#include "kiwi/Config.hpp"
#include "kiwi/DerivedTypes.hpp"

namespace kiwi {
    /// Internal class for store information of runtime types
    class ContextMeta {
    public:
        IntType* int32Ty;
        BoolType* boolTy;
        VoidType* voidTy;
        CharType* charTy;
        StringType* stringTy;
    };
}

#endif
