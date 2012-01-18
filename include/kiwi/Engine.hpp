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
    /// The Engine class represents general point for Kiwi
    /// @since 0.1
    class Engine {
    public:
        /// Engine constructor. This set up engine configuration
        Engine();

        /// Engine desctructor. This is clean up all resource requested by engine
        /// and
        ~Engine();
    }; // class Engine

    /// Startup Kiwi and related libraries
    /// @todo Must renamed to good name
    KIWI_API void startup();

    /// Shutdown Kiwi and related libraries
    /// @todo Must renamed to good name
    KIWI_API void shutdown();
} // namespace kiwi

#endif
