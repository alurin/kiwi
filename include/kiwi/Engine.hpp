/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_ENGINE_INCLUDED
#define KIWI_ENGINE_INCLUDED

#include "kiwi/Context.hpp"

namespace kiwi
{
    /// Start up Kiwi and prepare dependences
    void startup();

    /// Shut down Kiwi and clean up memory for dependences
    void shutdown();

    /// Guard for engine
    class EngineGuard {
    public:
        // constructor
        EngineGuard() { startup(); }

        // destructor
        ~EngineGuard() { shutdown(); }
    };

    ///
    class ContextEngine {
    public:
        ContextEngine() : m_context(0) {
            startup();
            m_context = Context::create();
        }

        ~ContextEngine() {
            delete m_context;
            shutdown();
        }

        Context* get() {
            return m_context;
        }
    protected:
        Context* m_context;
    };
}
#endif
