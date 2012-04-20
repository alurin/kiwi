#ifndef KIWI_MODULE_INCLUDED
#define KIWI_MODULE_INCLUDED

#include "kiwi/Config.hpp"

namespace llvm {
    class Module;
    class ExecutionEngine;
}

namespace kiwi
{
    typedef boost::shared_ptr<class Module>     ModuleRef;
    typedef boost::shared_ptr<class Context>  ContextRef;
    typedef boost::weak_ptr<class Context>    ContextWeak;

    #define FILE_SOURCE = 1; ///< File with source code
    #define FILE_VIEW   = 2; ///< File with view code

    class Module : public boost::enable_shared_from_this<Module>
    {
        Module(const Module&);            ///< NOT IMPLEMENT!!!
        Module& operator=(const Module&); ///< NOT IMPLEMENT!!!
    public:
        /// create module
        static ModuleRef create(const Identifier& name, const ContextRef& ref);

        /// include and run file as script
        void includeFile(const Path& filename);

        /// Returns module owner
        ContextRef getContext() const {
            return m_context.lock();
        }

        /// returns LLVM module
        llvm::Module* getModule() const {
            return m_module;
        }

        /// Build module
        void build();

        /// Dump module
        void dump();

        /// Run main function in module
        int32_t run();
    protected:
        Identifier              m_name;
        ContextWeak             m_context;
        llvm::Module*           m_module;
        llvm::ExecutionEngine*  m_engine;

        /// module constructor
        Module(const Identifier& name, const ContextRef& ref);
    };
}

#endif