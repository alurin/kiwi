/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_RUNTIME_GC_INCLUDED
#define KIWI_RUNTIME_GC_INCLUDED

#include "kiwi/config.hpp"
#include <stdint.h>
#include <stddef.h>

/// Allocate memory from GC
KIWI_RUNTIME
void* kiwi_malloc(int32_t size);

/// Allocat memory buffer from GC. This buffer must not containts pointers to
/// other GC allocated memory
KIWI_RUNTIME
void* kiwi_malloc_atomic(int32_t size);

#endif
