#include "string.h"

void *memset(void *dest, int ch, size_t count) {
  size_t dword_size = sizeof(unsigned int) / sizeof(unsigned char);
  size_t byte = 0;

  // Align to dword.
  for (; byte < (unsigned long)dest % dword_size; byte++) {
    ((unsigned char *)dest)[byte] = (unsigned char)ch;
  }

  // Set dword_size bytes at a time.
  for (; byte < count; byte += dword_size) {
    ((unsigned int *)dest)[byte / dword_size] = (unsigned int)ch;
  }

  // Set last bytes.
  for (; byte < count; byte++) {
    ((unsigned char *)dest)[byte] = (unsigned char)ch;
  }

  return dest;
}
