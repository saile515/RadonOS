#include "framebuffer.h"

#include <stdint.h>

uint32_t *framebuffer;
uint32_t framebuffer_width;
uint32_t framebuffer_height;

void framebuffer_init(uint32_t *buffer, uint32_t width, uint32_t height) {
  framebuffer = buffer;
  framebuffer_width = width;
  framebuffer_height = height;
}
