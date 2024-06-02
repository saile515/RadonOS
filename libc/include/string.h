#pragma once

#include <stddef.h>

char *strchr(const char *str, int ch);

void *memchr(const void *ptr, int ch, size_t count);
void *memset(void *dest, int ch, size_t count);
void *memcpy(void *restrict dest, const void *restrict src, size_t count);
