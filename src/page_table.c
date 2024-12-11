#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "constants.h"
#include "page_table.h"
#include "physical_memory.h"

PhysicalMemory physical_memory;

void initialize_page_table(PageTable *page_table, size_t num_pages) {
    page_table->num_pages = num_pages;
    page_table->entries = (PageTableEntry *)malloc(num_pages * sizeof(PageTableEntry));

    if (page_table->entries == NULL) {
        printf("Error: Memory allocation for page table entries failed!\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < num_pages; i++) {
        page_table->entries[i].frame_number = 0;
        page_table->entries[i].valid = false;
    }
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

void load_page(PageTable *page_table, uint16_t page_id, const char *data) {
    if (page_id >= page_table->num_pages) {
        printf("Error: Invalid page ID.\n");
        return;
    }

    int frame_id = find_free_frame();
    if (frame_id == -1) {
        printf("Error: No free frames available.\n");
        return;
    }

    // Update the page table
    update_page_table(page_table, page_id, frame_id);

    // Load the data into the frame
    physical_memory.frames[frame_id].data[0] = strdup(data);
    if (physical_memory.frames[frame_id].data == NULL) {
        printf("Error: Memory allocation for frame data failed!\n");
        return;
    }
}

void free_page_table(PageTable *page_table) {
    for (size_t i = 0; i < page_table->num_pages; i++) {
        if (page_table->entries[i].valid) {
            int frame_id = page_table->entries[i].frame_number;
            free(physical_memory.frames[frame_id].data); // Free data stored in the frame
            physical_memory.frames[frame_id].data[0] = NULL;
        }
    }

    free(page_table->entries);
    free(physical_memory.frames);

    page_table->entries = NULL;
    physical_memory.nums_frames = 0;
}
