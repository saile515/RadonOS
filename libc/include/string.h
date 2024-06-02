#pragma once

#include <stddef.h>

char *strchr(const char *string, int character);

void *memchr(const void *buffer, int character, size_t count);
void *memset(void *destination, int character, size_t count);
void *memcpy(void *restrict destination, const void *restrict source,
             size_t count);
