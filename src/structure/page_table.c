#include "structure/structure.h"

void initialize_page_table(PageTable *page_table)
{
    if (page_table->initialized)
    {
        fprintf(stderr, "Error: Page table already initialized.\n");
        exit(EXIT_FAILURE);
    }

    page_table->entries = (PageTableEntry *)malloc(sizeof(PageTableEntry) * PAGE_TABLE_ENTRIES);

    if (!page_table->entries)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    page_table->num_pages = 0;

    for (int i = 0; i < PAGE_TABLE_ENTRIES; ++i)
    {
        page_table->entries[i].frame_number = -1;
        page_table->entries[i].valid = false;
    }
}

int page_table_lookup(PageTable *page_table, int page_number)
{

    if (!page_table)
    {
        fprintf(stderr, "Error: Page table not initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (page_number >= PAGE_TABLE_ENTRIES || page_number < 0)
    {
        fprintf(stderr, "Error: Page number out of bounds.\n");
        exit(EXIT_FAILURE);
    }

    if (page_table->entries[page_number].valid)
        return page_table->entries[page_number].frame_number;

    return -1;
}

void link_page_table_to_frame(PageTable *page_table, int page_number, int frame_number)
{
    if (!page_table)
    {
        fprintf(stderr, "Error: Page table not initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (page_number >= PAGE_TABLE_ENTRIES || page_number < 0)
    {
        fprintf(stderr, "Error: Page number out of bounds.\n");
        exit(EXIT_FAILURE);
    }

    if (!page_table->entries[page_number].valid)
    {
        page_table->entries[page_number].valid = true;
        page_table->num_pages++;
    }
    page_table->entries[page_number].frame_number = frame_number;
}

void free_page_table(PageTable *page_table)
{
    free(page_table->entries);
    page_table->num_pages = 0;
}