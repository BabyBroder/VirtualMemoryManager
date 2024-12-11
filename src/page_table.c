#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "constants.h"
#include "page_table.h"

// Global static variables for physical memory frames
static Page *frames = NULL;
static int frame_count = 0;

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

    // Initialize physical memory frames
    frame_count = TOTAL_FRAMES;
    frames = (Page *)malloc(frame_count * sizeof(Page));
    if (frames == NULL) {
        printf("Error: Memory allocation for physical memory frames failed!\n");
        free(page_table->entries);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < frame_count; i++) {
        frames[i].data = NULL;
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

Page *get_page(PageTable *page_table, uint16_t page_id) {
    if (page_id >= page_table->num_pages || !page_table->entries[page_id].valid) {
        printf("Error: Invalid page ID or page not loaded.\n");
        return NULL;
    }

    int frame_id = page_table->entries[page_id].frame_number;
    return &frames[frame_id];
}

int find_free_frame() {
    for (int i = 0; i < frame_count; i++) {
        if (frames[i].data == NULL) { // Check if the frame is free
            return i;
        }
    }
    return -1; // No free frames available
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
    frames[frame_id].data = strdup(data);
    if (frames[frame_id].data == NULL) {
        printf("Error: Memory allocation for frame data failed!\n");
        return;
    }
}

void free_page_table(PageTable *page_table) {
    for (size_t i = 0; i < page_table->num_pages; i++) {
        if (page_table->entries[i].valid) {
            int frame_id = page_table->entries[i].frame_number;
            free(frames[frame_id].data); // Free data stored in the frame
            frames[frame_id].data = NULL;
        }
    }

    free(page_table->entries);
    free(frames);

    page_table->entries = NULL;
    frames = NULL;
    frame_count = 0;
}
