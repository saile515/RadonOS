#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

typedef struct file {
    uint8_t *buffer;
    size_t position;
} FILE;

extern FILE stdout_stream;

#define stdout &stdout_stream

int fputc(int character, FILE *stream);
int fprintf(FILE *stream, const char *format, ...);
int printf(const char *format, ...);
int putchar(int character);
int sprintf(char *buffer, const char *format, ...);
int vfprintf(FILE *stream, const char *format, va_list argp);
