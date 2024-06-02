#include "string.h"

#include <stdint.h>

void *memcpy(void *restrict dest, const void *restrict src, size_t count) {
  for (size_t i = 0; i < count; i++) {
    ((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
  }

  return dest;
}
