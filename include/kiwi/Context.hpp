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

        /// returns LLVM context
        llvm::LLVMContext& getContext() const {
            return *m_context;
        }

        /// returns internal context metadata
        ContextMeta* getMetadata() const {
            return m_meta;
        }

        /// Is scanner and parser debug mode
        bool isDebug() const {
            return m_debug;
        }

        /// Set scanner and parser debug mode
        void setDebug(bool debug) {
            m_debug = debug;
        }

        /// Returns optimization level
        int8_t getOptimizationLevel() {
            return m_optimizationLevel;
        }

        /// Set optimization level
        void setOptimizationLevel(int8_t level) {
            m_optimizationLevel = level;
        }
    protected:
        llvm::LLVMContext*  m_context;
        ContextMeta*        m_meta;

        int8_t              m_optimizationLevel;
        bool                m_debug;

        /// constructor
        Context();

        /// initilizator
        void initializate();
    };
}

#endif
