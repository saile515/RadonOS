#include "framebuffer.h"

#include <stdint.h>
#include <string.h>

uint32_t *framebuffer;
uint32_t framebuffer_width;
uint32_t framebuffer_height;

void framebuffer_init(uint32_t *buffer, uint32_t width, uint32_t height) {
  framebuffer = buffer;
  framebuffer_width = width;
  framebuffer_height = height;
}

void framebuffer_clear() {
  memset(framebuffer, 0,
         framebuffer_width * framebuffer_height * sizeof(uint32_t));
}
