#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stdint.h>
#include <stdbool.h>
#include "utils/constants.h"
#include "physical_memory.h"

// Structure for a page table entry
typedef struct {
    uint16_t frame_number; // Frame number in physical memory
    bool valid;            // Valid bit to indicate if the page is in memory
} PageTableEntry;

// Structure for the page table
typedef struct {
    PageTableEntry *entries; // Array of page table entries
    size_t num_pages;        // Total number of pages
} PageTable;

// Initializes the page table
void initialize_page_table(PageTable *page_table);

// Looks up the page table for a given page number
int page_table_lookup(PageTable *page_table, uint16_t page_number);

// Translates a logical page number to a frame number
// Returns -1 if the page is not valid (i.e., a page fault)
int translate_address(PageTable *page_table, uint32_t virtual_address);

// Updates the page table when a page is loaded into memory
void update_page_table(PageTable *page_table, uint16_t page_number, uint16_t frame_number);

// Gets the page by page number
Frame *get_page(PageTable *page_table, uint16_t page_id);

// Loads a page into memory
void load_page(PhysicalMemory *physical_memory, PageTable *page_table, uint16_t page_id, const char *data, int current_index);

// Cleans up resources allocated for the page table
void free_page_table(PhysicalMemory* physical_memory, PageTable *page_table);

#endif // PAGE_TABLE_H
