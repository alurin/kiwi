#ifndef KIWI_CONTEXTMETA_INTERNAL
#define KIWI_CONTEXTMETA_INTERNAL

#include "kiwi/Config.hpp"

namespace kiwi
{
    typedef boost::shared_ptr<class Type> TypeRef;

    class ContextMeta {
    public:
        TypeRef int32Ty;
        TypeRef boolTy;
        TypeRef voidTy;
        TypeRef charTy;
        TypeRef stringTy;
    };
}

#endif