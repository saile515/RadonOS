#include "framebuffer.h"
#include "multiboot.h"
#include "physical_memory.h"
#include "terminal.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void kernel_main(multiboot_info_t *multiboot_info, uint32_t magic) {
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        return;
    }

    init_physical_memory(
        (multiboot_memory_map_t *)(multiboot_info->mmap_addr + 0xC0000000),
        multiboot_info->mmap_length);

    framebuffer_init((uint32_t)multiboot_info->framebuffer_addr,
                     multiboot_info->framebuffer_width,
                     multiboot_info->framebuffer_height);

    terminal_init(framebuffer_width / 8, framebuffer_height / 16);

    printf("Welcome to RadonOS!\n");

    uint32_t pointer1 = (uint32_t)malloc(0x2000001);
    free((void *)pointer1);
    pointer1 = (uint32_t)malloc(0x4000001);
    uint32_t pointer2 = (uint32_t)malloc(0x20000000);
    uint32_t pointer3 = (uint32_t)malloc(0x2000000);

    printf("Pointer 1: %x\nPointer 2: %x\nPointer 3: %x", pointer1, pointer2,
           pointer3);

    terminal_render();
}
