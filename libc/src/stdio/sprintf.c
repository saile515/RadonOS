#include "math.h"
#include "stdio.h"
#include "string.h"
#include <stdarg.h>
#include <stdint.h>

int format_int(char *buffer, uint32_t number) {
    int magnitude = log10(number);

    uint32_t rest = number;

    for (int i = 0; i <= magnitude; ++i) {
        int multiplier = pow(10, magnitude - i);

        int digit = (rest / multiplier);

        rest -= digit * multiplier;

        buffer[i] = digit + '0';
    }

    buffer[magnitude + 1] = 0;

    return magnitude + 1;
}

int sprintf(char *buffer, const char *format, ...) {
    size_t length = strlen(format);
    size_t i = 0;
    char *buffer_ptr = buffer;

    va_list args;
    va_start(args, format);

    while (i < length) {
        if (format[i] != '%') {
            buffer_ptr[0] = format[i];
            ++buffer_ptr;
            ++i;
            continue;
        }

        char specifier = format[++i];

        if (specifier == 'd' || specifier == 'i') {
            buffer_ptr += format_int(buffer_ptr, va_arg(args, uint32_t));
            ++i;
            continue;
        }
    }

    va_end(args);

    buffer_ptr[0] = 0;

    return buffer_ptr - buffer;
}
