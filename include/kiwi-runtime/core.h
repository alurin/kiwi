#ifndef KIWI_RUNTIME_CORE
#define KIWI_RUNTIME_CORE

#include "kiwi-runtime/config.h"

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

#endif