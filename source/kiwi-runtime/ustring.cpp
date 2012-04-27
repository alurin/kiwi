/*
 *******************************************************************************
 *   Copyright (C) 2012 Vasiliy Sheredeko
 *   MIT license. All Rights Reserved.
 *******************************************************************************
 */
#include "kiwi-runtime/ustring.h"
#include "kiwi-runtime/gc.h"
#include <stdio.h>
#include <stdint.h>
#include <unicode/ustring.h>
#include <unicode/ustdio.h>
#include <unicode/utf.h>

#define KIWI_STRING_ALLOCA_EMPTY(_str) \
    _str = kiwi_malloc_atomic(sizeof(int32_t));    \
    int32_t* __destLength = (int32_t*) _str;    \
    *__destLength = 0;

// compare two strings
int8_t kiwi_string_compare(const UChar* buf1, const int32_t len1, const UChar* buf2, const int32_t len2) {
    return u_strCompare(buf1, len1, buf2, len2, false);
}


// return substring from ustring
UChar kiwi_subchar(const UChar* buffer, const int32_t length, const int32_t indexAt) {
    // @param s const UChar * string
    // @param start starting string offset (usually 0)
    // @param i string offset, must be start<=i<length
    // @param length string length
    // @param c output UChar32 variable
    // @see U16_GET_UNSAFE
    // @stable ICU 2.4
    // U16_GET(buffer, 0, indexAt, length, c);
    return buffer[indexAt];
}

// return substring from ustring
/// @todo REWRITE THIS!!!!!
void* kiwi_substring(const UChar* buffer, const int32_t length, int32_t indexAt, int32_t countAt) {
    // calculate index for first character in substring
    if (indexAt < 0) {
        indexAt = length + indexAt;
    }

    // calculate size of substring
    if (countAt == -1)
        countAt = length - indexAt;
    int32_t max = length - indexAt;
    countAt = countAt > max ? max : countAt;

    /// @todo Handle error situations
    if (max <= 0 || countAt <= 0 || (indexAt < 0 && indexAt > length - 1)) {
        void* empty = 0;
        KIWI_STRING_ALLOCA_EMPTY(empty);
        return empty;
    }

    // allocate memory for new string. BLA code
    // Get pointers for length and buffer
    void*    memory     = kiwi_malloc_atomic(sizeof(int32_t) + countAt * sizeof(UChar));
    int32_t* destLength = (int32_t*) memory;
    UChar*   dest       = (UChar*) (destLength + 1);
    UChar*   src        = (UChar*) (((void*) buffer) + (sizeof(UChar) * indexAt ));

    // copy substring
    *destLength = countAt;
    u_memcpy(dest, src, countAt);

    return memory;
}

//==------------------- THIS MUST HAVE REWRITED ----------------------------==//
void kiwi_print_integer(const int32_t value) {
    fprintf(stdout, "%d", value);
}

void kiwi_print_char(const UChar value) {
    UFILE *uout = u_finit(stdout, NULL, NULL);
    u_fprintf(uout, "%C", value);
}

void kiwi_print_bool(const int8_t value) {
    // UFILE *uout = u_finit(stdout, NULL, NULL);
    // u_fputc(value, uout);

    if (value) {
        fprintf(stdout, "true");
    } else {
        fprintf(stdout, "false");
    }
}

void kiwi_print_string(const UChar* buffer, const int32_t length) {
    UFILE *uout = u_finit(stdout, NULL, NULL);
    u_file_write(buffer, length, uout);
}
