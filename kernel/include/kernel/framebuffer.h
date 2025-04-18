#pragma once

#include <stdint.h>

extern uint32_t *framebuffer;
extern uint32_t framebuffer_width;
extern uint32_t framebuffer_height;

void framebuffer_init(uint32_t physical_buffer_address, uint32_t width,
                      uint32_t height);
void framebuffer_clear();
