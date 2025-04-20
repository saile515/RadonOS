#include "memory.h"

#include "math.h"
#include <stdint.h>

// TODO: Dynamically resize
memory_block_t memory_map[4096] = {{
    .allocated = 0,
    .branch0 = 0,
    .branch1 = 0,
}};

size_t memory_map_size = 1;

memory_block_t *get_block_from_trace(uint32_t block_trace_bitmap) {
    int trace_size = log2(block_trace_bitmap);

    block_trace_bitmap <<= 32 - trace_size;

    memory_block_t *current_block = &memory_map[0];

    for (int i = 0; i < trace_size; ++i) {
        uint32_t *next_block_index = (block_trace_bitmap & 0x80000000)
                                         ? &current_block->branch1
                                         : &current_block->branch0;

        if (*next_block_index == 0) {
            *next_block_index = memory_map_size;
            memory_block_t block = {};
            memory_map[memory_map_size++] = block;
        }

        current_block = &memory_map[*next_block_index];

        block_trace_bitmap <<= 1;
    }

    return current_block;
}

uint32_t get_block_trace_from_address(void *address) {
    uint32_t address_trace = (uint32_t)address;
    address_trace <<= 2;

    uint32_t trace = 0x1;

    memory_block_t *current_block = &memory_map[0];

    while (true) {
        uint32_t branch = address_trace & 0x80000000;

        uint32_t *next_block_index =
            branch ? &current_block->branch1 : &current_block->branch0;

        if (*next_block_index == 0) {
            break;
        }

        current_block = &memory_map[*next_block_index];

        address_trace <<= 1;
        trace <<= 1;

        if (branch) {
            trace |= 0x1;
        }
    }

    return trace;
}
