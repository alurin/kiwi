#ifndef KIWI_CONTEXTIMPL_INTERNAL
#define KIWI_CONTEXTIMPL_INTERNAL

#include "kiwi/Config.hpp"
#include "kiwi/DerivedTypes.hpp"
#include <vector>

namespace kiwi {
    /// Internal class for store information of runtime types
    class ContextImpl {
    public:
        ContextImpl();

        Module* runtime;
        IntType* int32Ty;
        BoolType* boolTy;
        VoidType* voidTy;
        CharType* charTy;
        StringType* stringTy;
        std::vector<Module*> modules;
    };
}

#endif
