#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct memory_block {
    bool allocated;
    uint32_t branch0;
    uint32_t branch1;
} memory_block_t;

memory_block_t *get_block_from_trace(uint32_t block_trace_bitmap);
uint32_t get_block_trace_from_address(void *address);

// TODO: Dynamically resize
extern memory_block_t memory_map[4096];

extern size_t memory_map_size;
