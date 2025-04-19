#include "stdlib.h"

#include "math.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct memory_block {
    bool allocated;
    uint32_t branch0;
    uint32_t branch1;
} memory_block_t;

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
            *next_block_index = memory_map_size++;
        }

        current_block = &memory_map[*next_block_index];

        block_trace_bitmap <<= 1;
    }

    return current_block;
}

void *malloc(size_t size) {
    int magnitude = log2(size);
    int target_depth = 31 - magnitude;

    uint32_t block_trace_bitmap = 0x1;

    while (true) {
        memory_block_t *current_block =
            get_block_from_trace(block_trace_bitmap);

        if (!current_block->allocated) {
            int depth = log2(block_trace_bitmap);

            if (depth != target_depth) {
                block_trace_bitmap <<= 1;
                continue;
            }

            if (!current_block->branch0 && !current_block->branch1) {
                current_block->allocated = true;
                break;
            }
        }

        while (block_trace_bitmap & 1) {
            if (block_trace_bitmap == 0x1) {
                return NULL;
            }

            block_trace_bitmap >>= 1;
        }

        ++block_trace_bitmap;
    }

    uint32_t address =
        ((block_trace_bitmap ^ (1 << target_depth)) << magnitude) | 0x40000000;

    return (void *)address;
}
