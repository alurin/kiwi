/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi-runtime/gc.h"

#ifdef KIWI_GC
    #include "gc.h"
#else
    #include <stdlib.h>
#endif

// Allocate memory from GC
void* kiwi_malloc(int32_t size) {
    KIWI_DUMP("Malloc " << size << " byte");
#ifdef KIWI_GC
    return GC_MALLOC(size);
#else
    return malloc(size);
#endif
}

// Allocat memory buffer from GC.
void* kiwi_malloc_atomic(int32_t size) {
    KIWI_DUMP("Malloc " << size << " byte");
#ifdef KIWI_GC
    return GC_MALLOC_ATOMIC(size);
#else
    return malloc(size);
#endif
}
