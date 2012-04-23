#ifndef KIWI_MODULEIMPL_INTERNAL
#define KIWI_MODULEIMPL_INTERNAL

#include "kiwi/Config.hpp"
#include <vector>

namespace kiwi {
    class Type;

    /// Internal class for store information of runtime types
    class ModuleImpl {
    public:
        std::vector<Type*> types;
    };
}

#endif
