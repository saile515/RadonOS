#include "framebuffer.h"

#include "paging.h"
#include <stdint.h>
#include <string.h>

#define FRAMEBUFFER_ADDRESS 0xFF800000

uint32_t *framebuffer = (uint32_t *)FRAMEBUFFER_ADDRESS;
uint32_t framebuffer_width;
uint32_t framebuffer_height;

void framebuffer_init(uint32_t physical_buffer_address, uint32_t width,
                      uint32_t height) {
    size_t framebuffer_page_count = width * height * 4 / 0x1000;

    for (size_t i = 0; i < framebuffer_page_count; ++i) {
        map_page(FRAMEBUFFER_ADDRESS + i * 0x1000,
                 physical_buffer_address + i * 0x1000, PAGE_WRITABLE);
    }

    framebuffer_width = width;
    framebuffer_height = height;
}

void framebuffer_clear() {
    memset(framebuffer, 0,
           framebuffer_width * framebuffer_height * sizeof(uint32_t));
}
