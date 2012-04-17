#ifndef KIWI_FRAMEWORK_INCLUDED
#define KIWI_FRAMEWORK_INCLUDED

#include "kiwi/Config.hpp"
#include "kiwi/Application.hpp"
#include <log4cxx/logger.h>

namespace llvm
{
    class LLVMContext;
}

namespace kiwi
{
    class Framework;
    typedef boost::shared_ptr<Framework> FrameworkRef;

    /**
     * General enter point for Kiwi compiler infrastructure
     *
     * @author Vasiliy Sheredeko
     * @since 2012-04-15
     */
    class Framework
    {
        Framework(const Framework&);                ///< NOT IMPLEMENT!!!
        Framework& operator=(const Framework&);     ///< NOT IMPLEMENT!!!

    public:
        /// create new instance and return smart reference for this instance
        static FrameworkRef create();

        /// destructor
        virtual ~Framework();

        /// returns Log4c++ logger
        log4cxx::LoggerPtr logger() const {
            return m_logger;
        }

        /// Returns LLVM context
        llvm::LLVMContext& getContext() const {
            return *m_context;
        }
    private:
        log4cxx::LoggerPtr  m_logger;
        llvm::LLVMContext*  m_context;

        Framework();
    };
}

#endif