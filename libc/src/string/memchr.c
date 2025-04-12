#include "string.h"

void *memchr(const void *buffer, int character, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (((unsigned char *)buffer)[i] == (unsigned char)character) {
            return ((void *)buffer) + i;
        }
    }

    return NULL;
}
