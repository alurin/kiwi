/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#ifndef KIWI_RUNTIME_USTRING_INCLUDED
#define KIWI_RUNTIME_USTRING_INCLUDED

#include "kiwi/config.hpp"
#include <stdint.h>
#include <unicode/utypes.h>

/**
 * return substring from ustring
 *
 * @param buffer    The input string
 * @param length    The number of UChar code units
 * @param indexAt   The index of character
 * @return          Character at @b indexAt place
 */
KIWI_RUNTIME
UChar kiwi_subchar(const UChar* buffer, const int32_t length, const int32_t indexAt);

/**
 * return substring from ustring
 *
 * @param buffer    The input string
 * @param length    The number of UChar code units
 * @param indexAt   The index of first character in substring, -1 from end of string
 * @param countAt   The count of characters in substring, -1 to the end of string
 * @return          Pointer for internal Kiwi string contains result substring
 */
KIWI_RUNTIME
void* kiwi_substring(const UChar* buffer, const int32_t length, int32_t indexAt, int32_t countAt);

/// Print integer value in output stream
KIWI_RUNTIME
void kiwi_print_integer(const int32_t value);

/// Print unicode character in ouput stream
KIWI_RUNTIME
void kiwi_print_char(const UChar value);

/// Print boolean value in ouput stream
KIWI_RUNTIME
void kiwi_print_bool(const int8_t value);

/// Print unicode string in output stream
KIWI_RUNTIME
void kiwi_print_string(const UChar* buffer, const int32_t length);

#endif
