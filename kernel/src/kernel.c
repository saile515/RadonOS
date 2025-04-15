#include "framebuffer.h"
#include "multiboot.h"
#include "terminal.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void kernel_main(multiboot_info_t *multiboot_info, uint32_t magic) {
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        return;
    }

    framebuffer_init((uint32_t *)(uint32_t)multiboot_info->framebuffer_addr,
                     multiboot_info->framebuffer_width,
                     multiboot_info->framebuffer_height);

    terminal_init(framebuffer_width / 8, framebuffer_height / 16);

    printf("Welcome to RadonOS!\n");

    for (size_t i = 0; i < multiboot_info->mmap_length;
         i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t *memory_map =
            (multiboot_memory_map_t *)(multiboot_info->mmap_addr + i);

        if (memory_map->type == MULTIBOOT_MEMORY_AVAILABLE) {
            printf("Start Addr: %x | Length: %x | Size: %x\n", memory_map->addr,
                   memory_map->len, memory_map->size, memory_map->type);
        }
    }

    terminal_render();
}
