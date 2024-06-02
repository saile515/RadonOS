#include "string.h"

#include <stddef.h>

char *strchr(const char *string, int character) {
  while (*string != (char)character) {
    if (*string == '\0') {
      return NULL;
    }

    string++;
  }

  return (char *)string;
}
