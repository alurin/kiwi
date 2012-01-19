/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_ENGINE_HPP_INCLUDED
#define KIWI_ENGINE_HPP_INCLUDED

#include "kiwi/Config.hpp"

/// Main namespace for all Kiwi core and releated compounds
namespace kiwi {
    class Host;

    /// The Engine class represents general point for Kiwi
    /// @since 0.1
    class Engine {
    public:
        /// Engine constructor. This set up engine configuration
        Engine(Host* host);

        /// Engine desctructor. This is clean up all resource requested by engine
        /// and
        ~Engine();

        /**
         * Returns engine host
         */
        Host* getHost() const {
            return m_host;
        }

    protected:
        Host* m_host;
    }; // class Engine

    /// Startup configuration Kiwi and related libraries
    class GlobalConfiguration {
    public:
        /// Startup Kiwi and related libraries
        GlobalConfiguration();

        /// Clean up Kiwi and related libraries
        /// @todo Verify LLVM clean up, valgrind show this is not worked
        ~GlobalConfiguration();
    };
} // namespace kiwi

#endif
