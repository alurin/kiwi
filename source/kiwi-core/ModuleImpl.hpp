/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_MODULEIMPL_INTERNAL
#define KIWI_MODULEIMPL_INTERNAL

#include "kiwi/config.hpp"
#include <set>
#include <map>

namespace llvm {
    class Module;
    class ExecutionEngine;
}

namespace kiwi {
    class Type;

    /// Internal class for store information of runtime types
    class ModuleImpl {
        friend class Module;
    public:
        /// returns LLVM module
        llvm::Module* getBackendModule() const {
            return m_backendModule;
        }

        /// create alias for type
        void registerType(TypePtr type, const Identifier& name);

        /// create alias for type
        void registerType(TypePtr type);
    private:
        /// module LLVM analog
        llvm::Module* m_backendModule;

        /// backend types
        std::set<TypePtr> m_types;

        /// map for named types
        std::map<Identifier, TypePtr> m_names;

        /// Main method for module
        MethodPtr mainMethod;

        /// constructor
        ModuleImpl();
    };
}

#endif
