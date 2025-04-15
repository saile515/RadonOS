#include "stdio.h"

#include "string.h"
#include "util.h"
#include <stdarg.h>

int fprintf(FILE *stream, const char *format, ...) {
    va_list argp;
    va_start(argp, format);

    int result = vfprintf(stream, format, argp);

    return result;
}

int vfprintf(FILE *stream, const char *format, va_list argp) {
    size_t length = strlen(format);
    size_t i = 0;
    size_t initial_position = stream->position;

    while (i < length) {
        if (format[i] != '%') {
            fputc(format[i], stream);
            ++stream->position;
            ++i;
            continue;
        }

        char specifier = format[++i];

        if (specifier == 'd' || specifier == 'i') {
            format_int(stream, va_arg(argp, uint32_t));
            ++i;
            continue;
        }

        if (specifier == 'x') {
            format_hex(stream, va_arg(argp, uint32_t));
            ++i;
            continue;
        }
    }

    return stream->position - initial_position;
}
