#include "string.h"

void *memcpy(void *restrict destination, const void *restrict source,
             size_t count) {
    for (size_t i = 0; i < count; i++) {
        ((unsigned char *)destination)[i] = ((unsigned char *)source)[i];
    }

    return destination;
}
