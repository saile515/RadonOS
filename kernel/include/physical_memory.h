#pragma once

#include "multiboot.h"
#include <stdint.h>

uint32_t allocate_physical_page();
void init_physical_memory(multiboot_memory_map_t *memory_map,
                          uint32_t memory_map_length);
