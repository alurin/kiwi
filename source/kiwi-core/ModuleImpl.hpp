#ifndef KIWI_MODULEIMPL_INTERNAL
#define KIWI_MODULEIMPL_INTERNAL

#include "kiwi/Config.hpp"
#include <vector>

namespace kiwi {
    class Type;

    /// Internal class for store information of runtime types
    class ModuleImpl {
        friend class Module;
    private:
        ModuleImpl() : mainMethod(0) { }
    public:
        std::vector<Type*> types;
        Method*            mainMethod;
    };
}

#endif
