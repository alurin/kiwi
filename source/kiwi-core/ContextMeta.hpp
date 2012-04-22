#ifndef KIWI_CONTEXTMETA_INTERNAL
#define KIWI_CONTEXTMETA_INTERNAL

#include "kiwi/Config.hpp"
#include "kiwi/DerivedTypes.hpp"

namespace kiwi
{
    class ContextMeta {
    public:
        IntTy       int32Ty;
        BoolTy      boolTy;
        VoidTy      voidTy;
        CharTy      charTy;
        StringTy    stringTy;
    };
}

#endif