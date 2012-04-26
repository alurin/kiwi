/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi-runtime/gc.h"
#include "gc.h"

// Allocate memory from GC
void* kiwi_malloc(size_t size) {
    return GC_MALLOC(size);
}

// Allocat memory buffer from GC.
void* kiwi_malloc_atomic(size_t size) {
    return GC_MALLOC_ATOMIC(size);
}
