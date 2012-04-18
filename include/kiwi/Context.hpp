#ifndef KIWI_CONTEXT_INCLUDED
#define KIWI_CONTEXT_INCLUDED

#include "kiwi/Config.hpp"
#include "kiwi/Application.hpp"
#include <log4cxx/logger.h>

namespace llvm
{
    class LLVMContext;
}

namespace kiwi
{
    /// Internal framework metadata
    class ContextMeta;
    class Context;
    typedef boost::shared_ptr<Context> ContextRef;

    /**
     * General enter point for Kiwi compiler infrastructure
     *
     * @author Vasiliy Sheredeko
     * @since 2012-04-15
     */
    class Context : public boost::enable_shared_from_this<Context>
    {
        Context(const Context&);                ///< NOT IMPLEMENT!!!
        Context& operator=(const Context&);     ///< NOT IMPLEMENT!!!

    public:
        /// create new instance and return smart reference for this instance
        static ContextRef create();

        /// destructor
        virtual ~Context();

        /// returns Log4c++ logger
        log4cxx::LoggerPtr logger() const {
            return m_logger;
        }

        /// Returns LLVM context
        llvm::LLVMContext& getContext() const {
            return *m_context;
        }
    protected:
        log4cxx::LoggerPtr  m_logger;
        llvm::LLVMContext*  m_context;
        ContextMeta*      m_meta;

        /// constructor
        Context();

        /// initilizator
        void initializate();
    };
}

#endif