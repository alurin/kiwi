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
void* kiwi_malloc(size_t size) {
#ifdef KIWI_GC
    void* pointer = GC_MALLOC(size);
#else
    void* pointer = calloc(1, size);
#endif
    // KIWI_DUMP("Allocate " << size << " at " << pointer);
    return pointer;
}

// Allocat memory buffer from GC.
void* kiwi_malloc_atomic(size_t size) {
#ifdef KIWI_GC
    void* pointer = GC_MALLOC_ATOMIC(size);
#else
    void* pointer = calloc(1, size);
#endif
    // KIWI_DUMP("Allocate " << size << " at " << pointer);
    return pointer;
}
