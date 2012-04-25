#ifndef KIWI_MODULE_INCLUDED
#define KIWI_MODULE_INCLUDED

#include "kiwi/config.hpp"
#include <vector>
#include <map>

namespace llvm {
    class Module;
    class ExecutionEngine;
}

namespace kiwi
{
    class Context;
    class Type;
    class Method;
    /// Storage for internal module metadata
    class ModuleImpl;

    /// Assembly of types
    class Module {
        Module(const Module&);            ///< NOT IMPLEMENT!!!
        Module& operator=(const Module&); ///< NOT IMPLEMENT!!!
    public:
        /// destructor
        ~Module();

        /// create module
        static Module* create(const Identifier& name, Context* ref);

        /// returns internal context metadata
        ModuleImpl* getMetadata() const {
            return m_metadata;
        }

        /// include and run file as script
        bool includeFile(const Path& filename);

        /// returns module owner
        Context* getContext() const {
            return m_context;
        }

        /// returns LLVM module
        llvm::Module* getModule() const {
            return m_module;
        }

        /// create alias for type
        void registerType(Type* type, const Identifier& name);

        /// find type with name
        Type* find(const Identifier& name);

        /// returns main method in current module
        Method* getMainMethod();

        /// build module
        void build();

        /// dump module
        void dump();

        /// run main function in module
        int32_t run();
    protected:
        /// module name
        Identifier m_name;

        /// module context
        Context* m_context;

        /// module internal metadata
        ModuleImpl* m_metadata;

        /// module LLVM analog
        llvm::Module* m_module;

        /// module runtime engine
        llvm::ExecutionEngine* m_engine;

        /// list of all module types
        std::vector<Type*> m_types;

        /// map for named types
        std::map<Identifier, Type*> m_names;

        /// module constructor
        Module(const Identifier& name, Context* ref);
    };
}

#endif
