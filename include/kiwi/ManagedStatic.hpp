/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_MANAGEDSTATIC_INCLUDED
#define KIWI_MANAGEDSTATIC_INCLUDED

namespace kiwi {
    /// Initialize resources for vendor libraries
    void startup();

    /// Clean up resource for vendor libraries
    void shutdown();

    /// Guard for initialize and clean up resources used internaly by Kiwi
    /// ifrastructure
    class ManagedStatic {
    public:
        /// Initialize resources for vendor libraries
        ManagedStatic() {
            startup();
        }

        /// Clean up resource for vendor libraries
        ~ManagedStatic() {
            shutdown();
        }
    };
}

#endif
