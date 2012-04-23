#ifndef KIWI_MODULE_INCLUDED
#define KIWI_MODULE_INCLUDED

#include "kiwi/Config.hpp"
#include <vector>

namespace llvm {
    class Module;
    class ExecutionEngine;
}

namespace kiwi
{
    class Context;
    class Type;
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
        void includeFile(const Path& filename);

        /// returns module owner
        Context* getContext() const {
            return m_context;
        }

        /// returns LLVM module
        llvm::Module* getModule() const {
            return m_module;
        }

        /// build module
        void build();

        /// dump module
        void dump();

        /// run main function in module
        int32_t run();
    protected:
        /// module name
        Identifier              m_name;
        Context*                m_context;
        ModuleImpl*             m_metadata;
        llvm::Module*           m_module;
        llvm::ExecutionEngine*  m_engine;
        std::vector<Type*>      m_types;

        /// module constructor
        Module(const Identifier& name, Context* ref);
    };
}

#endif
