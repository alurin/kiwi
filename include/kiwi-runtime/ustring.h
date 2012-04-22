#ifndef KIWI_RUNTIME_USTRING
#define KIWI_RUNTIME_USTRING

#include "kiwi-runtime/config.h"
#include <stdint.h>
#include <unicode/utypes.h>

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
