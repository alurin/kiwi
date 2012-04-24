#ifndef KIWI_RUNTIME_USTRING
#define KIWI_RUNTIME_USTRING

#include "kiwi-runtime/config.h"
#include <stdint.h>
#include <unicode/utypes.h>

/**
 * return substring from ustring
 *
 * @param buffer
 * @param lenght
 * @param indexAt
 */
KIWI_RUNTIME
int32_t kiwi_subchar(UChar* buffer, int32_t lenght, int32_t indexAt);

/**
 * return substring from ustring
 *
 * @param buffer
 * @param lenght
 * @param indexAt
 * @param countAt
 */
KIWI_RUNTIME
int32_t kiwi_substring(UChar* buffer, int32_t lenght, int32_t indexAt, int32_t countAt);

/// Print integer value in output stream
KIWI_RUNTIME
void kiwi_print_integer(int32_t value);

/// Print unicode character in ouput stream
KIWI_RUNTIME
void kiwi_print_char(UChar value);

/// Print boolean value in ouput stream
KIWI_RUNTIME
void kiwi_print_bool(int8_t value);

/// Print unicode string in output stream
KIWI_RUNTIME
void kiwi_print_string(UChar* buffer, int32_t lenght);

#endif
