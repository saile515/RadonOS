#include "stdlib.h"

#include "memory.h"
#include "string.h"

void free(void *pointer) {
    uint32_t block_trace = get_block_trace_from_address(pointer);

    while (true) {
        uint32_t branch = block_trace & 0x1;
        memory_block_t *parent = get_block_from_trace(block_trace >>= 1);

        uint32_t block_index = branch ? parent->branch1 : parent->branch0;
        uint32_t sibling_index = branch ? parent->branch0 : parent->branch1;

        memory_block_t empty_block = {};

        memory_map[block_index] = empty_block;

        if (sibling_index != 0) {
            memory_map[sibling_index] = empty_block;
            break;
        }

        parent->branch0 = 0;
        parent->branch1 = 0;

        --memory_map_size;

        memmove(&memory_map[block_index], &memory_map[block_index + 1],
                (memory_map_size - block_index) * sizeof(memory_block_t));

        if (parent == &memory_map[0]) {
            break;
        }
    }
}
