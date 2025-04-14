#include "stdio.h"
#include <stdarg.h>
#include <stdint.h>

int sprintf(char *buffer, const char *format, ...) {
    FILE file = {.buffer = (uint8_t *)buffer, .position = 0};

    int result = fprintf(&file, format);

    buffer[file.position] = 0;

    return result;
}
