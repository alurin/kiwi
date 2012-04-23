#include "kiwi-runtime/ustring.h"
#include <stdio.h>
#include <stdint.h>
#include <unicode/ustring.h>
#include <unicode/ustdio.h>

void kiwi_print_integer(int32_t value) {
    fprintf(stdout, "%d", value);
}

void kiwi_print_char(UChar value) {
    UFILE *uout = u_finit(stdout, NULL, NULL);
    u_fprintf(uout, "%C", value);
}

void kiwi_print_bool(int8_t value) {
    // UFILE *uout = u_finit(stdout, NULL, NULL);
    // u_fputc(value, uout);

    if (value) {
        fprintf(stdout, "true");
    } else {
        fprintf(stdout, "false");
    }
}

void kiwi_print_string(UChar* buffer, int32_t lenght) {
    UFILE *uout = u_finit(stdout, NULL, NULL);
    u_file_write(buffer, lenght, uout);
}
