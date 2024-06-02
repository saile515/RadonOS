#include "string.h"

void *memchr(const void *ptr, int ch, size_t count) {
  for (size_t i = 0; i < count; i++) {
    if (((unsigned char *)ptr)[i] == (unsigned char)ch) {
      return ((void *)ptr) + i;
    }
  }

  return NULL;
}
