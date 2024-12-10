#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_table.h"

PageTableEntry *page_table = NULL;
Page *frames = NULL;
int page_table_size = 256;
int frame_count = 0;

void initialize_page_table(PageTable *page_table, size_t num_pages)
{
    page_table->entries = (PageTableEntry *)malloc(num_pages * sizeof(PageTableEntry));
    page_table->num_pages = num_pages;
    for (size_t i = 0; i < num_pages; i++)
    {
        page_table->entries[i].frame_number = -1; // not mapped
        page_table->entries[i].valid = false;
    }

    frame_count = num_pages;
    frames = (Page *)malloc(num_pages * sizeof(Page)); // Allocate memory for the frames
    for (int i = 0; i < num_pages; i++)
    {
        frames[i].data = NULL; // Initialize data pointer to NULL
    }
}

// Translate a logical page number to a frame number
// Returns -1 if the page is not valid (i.e., a page fault)
int translate_address(PageTable *page_table, uint16_t page_number)
{
    if (page_number >= page_table->num_pages || !page_table->entries[page_number].valid)
    {
        printf("Error: Invalid virtual address or page not loaded!\n");
        return -1;
    }
    return page_table->entries[page_number].frame_number;
}

// Update the page table with the frame number when a page is loaded into memory
void update_page_table(PageTable *page_table, uint16_t page_number, uint16_t frame_number)
{
    if (page_number >= page_table->num_pages)
    {
        printf("Error: Invalid page number!\n");
        return;
    }
    page_table->entries[page_number].frame_number = frame_number;
    page_table->entries[page_number].valid = true;
}

// Get the page by page ID
Page *get_page(PageTable *page_table, uint16_t page_id)
{
    if (page_id >= page_table->num_pages || !page_table->entries[page_id].valid)
    {
        printf("Error: Page is not valid or does not exist!\n");
        return NULL;
    }

    return &frames[page_table->entries[page_id].frame_number];
}

// Load a page into memory
void load_page(PageTable *page_table, uint16_t page_id, const char *data)
{
    if (page_id >= page_table->num_pages)
    {
        printf("Error: Invalid page ID.\n");
        return;
    }
    int frame_id = page_id; // For simplicity, assume 1-to-1 mapping of pages to frames
    update_page_table(page_table, page_id, frame_id);
    frames[frame_id].data = strdup(data); // Copy the data into the page
}

// Clean up resources allocated for the page table
void free_page_table(PageTable *page_table)
{
    for (int i = 0; i < frame_count; i++)
    {
        free(frames[i].data);
    }
    free(frames);
    free(page_table->entries);
}
