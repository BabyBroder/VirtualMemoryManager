#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "page_table.h"
#include "physical_memory.h"

PhysicalMemory physical_memory;

void initialize_page_table(PageTable *page_table) {
    page_table->num_pages = PAGE_TABLE_ENTRIES;
    page_table->entries = (PageTableEntry *)malloc(PAGE_TABLE_ENTRIES * sizeof(PageTableEntry));

    if (page_table->entries == NULL) {
        printf("Error: Memory allocation for page table entries failed!\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < PAGE_TABLE_ENTRIES; i++) {
        page_table->entries[i].frame_number = 0;
        page_table->entries[i].valid = false;
    }
}

int page_table_lookup(PageTable *page_table, uint16_t page_number) {
    if (page_number < 0 || page_number >= page_table->num_pages || !page_table->entries[page_number].valid) {
        return -1;
    }

    return page_table->entries[page_number].frame_number;
}

int translate_address(PageTable *page_table, uint32_t virtual_address) {
    const uint16_t PAGE_OFFSET_BITS = 8;
    const uint16_t PAGE_NUMBER_BITS = 16 - PAGE_OFFSET_BITS;

    uint16_t page_number = (virtual_address >> PAGE_OFFSET_BITS) & ((1 << PAGE_NUMBER_BITS) - 1);
    uint16_t offset = virtual_address & ((1 << PAGE_OFFSET_BITS) - 1);

    if (page_number >= page_table->num_pages || !page_table->entries[page_number].valid) {
        printf("Error: Invalid virtual address or page not loaded!\n");
        return -1;
    }

    int frame_id = page_table->entries[page_number].frame_number;
    int physical_address = frame_id * FRAME_SIZE + offset;

    return physical_address;
}

void update_page_table(PageTable *page_table, uint16_t page_number, uint16_t frame_number) {
    if (page_number >= page_table->num_pages) {
        printf("Error: Invalid page number.\n");
        return;
    }

    page_table->entries[page_number].frame_number = frame_number;
    page_table->entries[page_number].valid = true;
}

Frame *get_page(PageTable *page_table, uint16_t page_id) {
    if (page_id >= page_table->num_pages || !page_table->entries[page_id].valid) {
        printf("Error: Invalid page ID or page not loaded.\n");
        return NULL;
    }

    int frame_id = page_table->entries[page_id].frame_number;
    return &physical_memory.frames[frame_id];
}

void load_page(PhysicalMemory *physical_memory, PageTable *page_table, uint16_t page_id, const char *data, int current_index) {
    if (page_id >= page_table->num_pages) {
        printf("Error: Invalid page ID.\n");
        return;
    }

    int frame_id = find_free_frame(physical_memory, current_index);
    if (frame_id == -1) {
        printf("Error: No free frames available.\n");
        return;
    }

    // Update the page table
    update_page_table(page_table, page_id, frame_id);

    // Load the data into the frame
    strncpy(physical_memory->frames[frame_id].data, data, FRAME_SIZE);
    physical_memory->frames[frame_id].data[FRAME_SIZE - 1] = '\0';
}

void free_page_table(PhysicalMemory* physical_memory, PageTable *page_table) {
    for (size_t i = 0; i < page_table->num_pages; i++) {
        if (page_table->entries[i].valid) {
            int frame_id = page_table->entries[i].frame_number;
            memset(physical_memory->frames[frame_id].data, 0, FRAME_SIZE); // Clear data stored in the frame
        }
    }

    free(page_table->entries);
    free(physical_memory->frames);

    page_table->entries = NULL;
    physical_memory->nums_frames = 0;
}
