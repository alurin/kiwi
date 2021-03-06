/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_CONTEXT_INCLUDED
#define KIWI_CONTEXT_INCLUDED

#include "kiwi/types.hpp"

namespace kiwi {
    /// Storage for internal context metadata
    class ContextImpl;

    /// Typedef for smart reference for context
    typedef boost::shared_ptr<class Context> ContextPtr;

    /**
     * General enter point for Kiwi language infrastructure
     *
     * @todo Create multiple contextes is crashed application: errors with ICU and LLVM.
     *       View guard
     */
    class Context : public boost::enable_shared_from_this<Context>, public boost::noncopyable {
    public:
        /// create new instance of context
        static ContextPtr create();

        /// destructor
        virtual ~Context();

        /// returns internal context metadata
        ContextImpl* getMetadata() const {
            return m_metadata;
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

        /// Run main method from module and return result
        int32_t run(ModulePtr module);
    protected:
        ContextImpl*        m_metadata;

        int8_t              m_optimizationLevel;
        bool                m_debug;

        /// constructor
        Context();

        /// initilizator
        void initializate();
    };
}

#endif
