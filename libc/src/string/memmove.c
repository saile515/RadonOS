#include "string.h"

#include <limits.h>
#include <stdbool.h>

void *memmove(void *destination, const void *source, size_t count) {
    bool reverse = destination > source;

    if (reverse) {
        for (size_t i = count - 1; i < UINT_MAX; --i) {
            ((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
        }
    } else {
        for (size_t i = 0; i < count; ++i) {
            ((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
        }
    }

    return destination;
}
