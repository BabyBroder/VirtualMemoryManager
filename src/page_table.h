#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stdint.h>
#include <stdbool.h>

// Structure for a page table entry
typedef struct {
    uint16_t frame_number; // Frame number in physical memory
    bool valid;            // Valid bit to indicate if the page is in memory
} PageTableEntry;

// Structure for a physical memory page
typedef struct {
    char *data;            // Placeholder for page data (for simplicity, assume it holds a string)
} Page;

// Structure for the page table
typedef struct {
    PageTableEntry *entries; // Array of page table entries
    size_t num_pages;        // Total number of pages
} PageTable;

// Initializes the page table
void initialize_page_table(PageTable *page_table, size_t num_pages);
// Initializes physical memory
void initialize_physical_memory(PageTable *page_table, const char *file_path);
// Translates a logical page number to a frame number
// Returns -1 if the page is not valid (i.e., a page fault)
int translate_address(PageTable *page_table, uint32_t virtual_address);

// Updates the page table when a page is loaded into memory
void update_page_table(PageTable *page_table, uint16_t page_number, uint16_t frame_number);

// Gets the page by page number
Page *get_page(PageTable *page_table, uint16_t page_id);

// Finds a free frame in physical memory
int find_free_frame();

// Loads a page into memory
void load_page(PageTable *page_table, uint16_t page_id, const char *data);

// Cleans up resources allocated for the page table
void free_page_table(PageTable *page_table);

#endif // PAGE_TABLE_H
