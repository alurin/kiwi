/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_ASSERT_INCLUDED
#define KIWI_ASSERT_INCLUDED

#include "kiwi/config.hpp"

#ifdef KIWI_DEBUG
#   include <assert.h>
    /// Assertion
#   define kiwi_assert(_expr, _message) assert((_expr) && _message);
#else
    /// Dummy assert
#   define kiwi_assert(_expr, _message)
#endif

/// @todo Runtime assertion
#define kiwi_runtime_assert(_expr, _message) assert((_expr) && _message);

#endif
