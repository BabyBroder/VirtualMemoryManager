#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_table.h"
#include "utils/constants.h"

static Page *frames = NULL;
static int frame_count = 0;

void initialize_page_table(PageTable *page_table) {
    page_table->num_pages = PAGE_TABLE_ENTRIES;
    page_table->entries = (PageTableEntry *)malloc(PAGE_TABLE_ENTRIES * sizeof(PageTableEntry));
    frames = (Page *)malloc(PAGE_TABLE_ENTRIES * sizeof(Page));
    frame_count = PAGE_TABLE_ENTRIES;
    
    for (size_t i = 0; i < PAGE_TABLE_ENTRIES; i++) {
        page_table->entries[i].frame_number = -1; // Not mapped initially
        page_table->entries[i].valid = false;
        frames[i].data = ""; // Initialize data as empty
    }
}

int translate_address(PageTable *page_table, uint16_t page_number) {
    if (page_number >= page_table->num_pages || !page_table->entries[page_number].valid) {
        printf("Error: Invalid virtual address or page not loaded!\n");
        return -1;
    }
    
    int frame_id = page_table->entries[page_number].frame_number;
    int physical_address = frame_id * PAGE_SIZE; // Calculate physical address from frame and page size
    return physical_address;
}

void update_page_table(PageTable *page_table, uint16_t page_number, uint16_t frame_number) {
    if (page_number >= page_table->num_pages) {
        printf("Error: Invalid page ID!\n");
        return;
    }
    
    page_table->entries[page_number].frame_number = frame_number;
    page_table->entries[page_number].valid = true;
}

Page* get_page(PageTable *page_table, uint16_t page_id) {
    if (page_id >= page_table->num_pages || !page_table->entries[page_id].valid) {
        printf("Error: Page is not valid!\n");
        return NULL;
    }

    return &frames[page_table->entries[page_id].frame_number];
}

void load_page(PageTable *page_table, uint16_t page_id, const char *data) {
    if (page_id >= page_table->num_pages) {
        printf("Error: Invalid page ID.\n");
        return;
    }

    int frame_id = page_id; // Assuming the page and frame are 1:1 for simplicity
    update_page_table(page_table, page_id, frame_id);
    frames[frame_id].data = (char *)data; // Load page data into the frame
}

void free_page_table(PageTable *page_table) {
    free(page_table->entries);
    free(frames); // Free the frame data
    page_table->entries = NULL;
    frames = NULL;
}
