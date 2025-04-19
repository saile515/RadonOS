#include <stddef.h>
#include <stdint.h>

#include "paging.h"
#include "physical_memory.h"

uint32_t get_page_table_address(uint32_t page_table_entry) {
    return page_table_entry & PAGE_ADDRESS;
}

bool is_page_present(uint32_t page_table_entry) {
    return page_table_entry & PAGE_PRESENT;
}

uint32_t *page_directory = (uint32_t *)0xFFFFF000;

bool map_page(uint32_t virtual_address, uint32_t physical_address,
              unsigned int flags) {
    size_t page_directory_index = (uint32_t)virtual_address >> 22;
    size_t page_table_index = (uint32_t)virtual_address >> 12 & 0x03FF;

    if (!is_page_present(page_directory[page_directory_index])) {
        page_directory[page_directory_index] = allocate_physical_page() | 0x3;
    }

    uint32_t *page_table =
        ((uint32_t *)0xFFC00000) + (0x400 * page_directory_index);

    if (is_page_present(page_table[page_table_index])) {
        // return false;
    }

    page_table[page_table_index] = physical_address | (flags & 0xFFF) | 0x1;

    __asm__("movl %cr3, %eax\n\tmovl %eax, %cr3");

    return true;
}
