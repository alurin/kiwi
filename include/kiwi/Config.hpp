/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */

#ifndef KIWI_CONFIG_HPP_INCLUDED
#define KIWI_CONFIG_HPP_INCLUDED



///==--------------------------------------------------------------------------------------------------------------==///
///   Assetions
///==--------------------------------------------------------------------------------------------------------------==///

#ifndef kiwi_assert
#   include <cassert>
#   define kiwi_assert(exp) assert(exp)
#endif

#ifdef KIWI_DEBUG
#   define KIWI_DEBUG_ASSERT(exp) kiwi_assert(exp)
#else
#   define KIWI_DEBUG_ASSERT(exp) ((void)0)
#endif

#endif
