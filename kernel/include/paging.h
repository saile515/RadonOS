#pragma once

#include <stdbool.h>
#include <stdint.h>

#define PAGE_ADDRESS 0xFFFFFF000
#define PAGE_WRITABLE 0x000000002
#define PAGE_PRESENT 0x000000001

extern uint32_t *page_directory;

bool map_page(uint32_t virtual_address, uint32_t physical_address,
              unsigned int flags);
uint32_t get_page_address(uint32_t page_table_entry);
bool is_page_present(uint32_t page_table_entry);
