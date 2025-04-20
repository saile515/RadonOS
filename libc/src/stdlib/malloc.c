#include "stdlib.h"

#include "math.h"
#include "memory.h"
#include <stdbool.h>
#include <stdint.h>

void *malloc(size_t size) {
    int magnitude = log2(size - 1) + 1;
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

        block_trace_bitmap |= 1;
    }

    uint32_t address =
        ((block_trace_bitmap ^ (1 << target_depth)) << magnitude) + 0x40000000;

    return (void *)address;
}
