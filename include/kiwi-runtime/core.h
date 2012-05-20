/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_RUNTIME_CORE_INCLUDED
#define KIWI_RUNTIME_CORE_INCLUDED

#include "kiwi/config.hpp"
#include <stdint.h>

/// Type for virtual table
typedef void*       KiwiVTable;

/// Type for address map
typedef int32_t*    KiwiAMap;

/// Opaque structure for Kiwi type (e.g. kiwi::Type)
typedef struct KiwiOpaqueType *KiwiType;

/// Type for type. This type has dynamic size
typedef struct KiwiOpaqueData {
    KiwiType Type;
} *KiwiData;


/// Basic layout for standart Kiwi object
typedef struct KiwiOpaqueObject {
    /// Pointer to current pointer to dynamic virtual table
    KiwiVTable* VTable;

    /// Pointer to current pointer to dynamic address map
    KiwiAMap* AMap;

    /// Pointer to current data buffer
    KiwiData Data;
} *KiwiObject;

/// Start up kiwi runtime and prepare dependences
KIWI_RUNTIME
void kiwi_startup();

/// Shut down kiwi runtime and clean up memory for dependences
KIWI_RUNTIME
void kiwi_shutdown();

/// Dummy function for link runtime library in core library
KIWI_RUNTIME
void kiwi_dummy();

/// Include file with Kiwi source code and execute, if avaible
KIWI_RUNTIME
void kiwi_include(const char* filename);

/// Cast up to inheritance tree
KIWI_RUNTIME
KiwiObject kiwi_up_cast(KiwiObject object, KiwiType type);

/// Cast down to inheritance tree
KIWI_RUNTIME
KiwiObject kiwi_down_cast(KiwiObject object, KiwiType type);

#endif
