#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdint.h>
#include <stdbool.h>
#include "page_table.h"
#include "tlb.h"

// Function to initialize memory management components
void initialize_memory_manager(PageTable *page_table, TLB *tlb, size_t num_frames);

// Function to translate a virtual address to a physical address
// Returns -1 if the address translation fails (page fault)
int translate_address(PageTable *page_table, TLB *tlb, uint32_t virtual_address);

// Function to load a page into memory
void load_page(PageTable *page_table, TLB *tlb, uint16_t page_id, const char *data);

// Function to evict a page from memory using the TLB
void evict_page(PageTable *page_table, TLB *tlb, uint16_t page_id);

// Function to handle a page fault by loading the page into memory from the disk
void handle_page_fault(int page_number);

#endif // MEMORY_MANAGER_H
