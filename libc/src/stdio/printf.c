#include "stdio.h"

int printf(const char *format, ...) {
    va_list argp;
    va_start(argp, format);

    int result = vfprintf(stdout, format, argp);

    va_end(argp);
    return result;
};
