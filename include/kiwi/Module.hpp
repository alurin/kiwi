#ifndef KIWI_MODULE_INCLUDED
#define KIWI_MODULE_INCLUDED

#include "kiwi/Config.hpp"

namespace llvm {
    class Module;
    class ExecutionEngine;
}

namespace kiwi
{
    class Context;

    class Module {
        Module(const Module&);            ///< NOT IMPLEMENT!!!
        Module& operator=(const Module&); ///< NOT IMPLEMENT!!!
    public:
        /// destructor
        ~Module();

        /// create module
        static Module* create(const Identifier& name, Context* ref);

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
        llvm::Module*           m_module;
        llvm::ExecutionEngine*  m_engine;

        /// module constructor
        Module(const Identifier& name, Context* ref);
    };
}

#endif
