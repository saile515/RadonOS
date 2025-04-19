#include "physical_memory.h"
#include "multiboot.h"

#include <stddef.h>
#include <string.h>

uint32_t page_availability_map[32768];

uint32_t allocate_physical_page() {
    int i = 0;

    while (page_availability_map[i] == 0x0) {
        ++i;
    }

    int page_index = 0;

    while (((page_availability_map[i] >> page_index) & 0x1) != 0x1) {
        ++page_index;
    }

    page_availability_map[i] ^= (0x1 << page_index);

    page_index += i * 32;

    return page_index * 0x1000;
}

void init_physical_memory(multiboot_memory_map_t *memory_map,
                          uint32_t memory_map_length) {
    memset(page_availability_map, 0x0, sizeof(page_availability_map));

    for (size_t i = 0; i < memory_map_length / sizeof(multiboot_memory_map_t);
         ++i) {
        if (memory_map[i].type != MULTIBOOT_MEMORY_AVAILABLE) {
            continue;
        }

        int offset = memory_map[i].addr >> 12;

        int size = memory_map[i].len / 4096 / 32;

        memset(page_availability_map + offset, 0xFF, size);
    }

    memset(page_availability_map, 0x0, 0x1000);
}
