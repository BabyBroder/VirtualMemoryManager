#include "../../lib/structure/structure.h"

/**
 * Initializes the page table with the given number of pages.
 *
 * @param page_table A pointer to the PageTable structure.
 */
void initialize_page_table(PageTable *page_table)
{
    if (page_table)
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

/**
 * Looks up the page table for a given page number.
 *
 * @param page_table A pointer to the PageTable structure.
 * @param page_number The page number to look up.
 * @return The frame number corresponding to the page number, or -1 if the page is not found.
 */
int page_table_lookup(PageTable *page_table, uint16_t page_number)
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

/**
 * Updates the page table when a page is loaded into memory.
 *
 * @param page_table A pointer to the PageTable structure.
 * @param page_number The page number to be updated.
 * @param frame_number The frame number to be associated with the page number.
 */
void link_page_table_to_frame(PageTable *page_table, uint16_t page_number, uint16_t frame_number)
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

/**
 * Cleans up resources allocated for the page table.
 * @param page_table A pointer to the PageTable structure to be freed.
 */
void free_page_table(PageTable *page_table)
{
    free(page_table->entries);
    page_table->num_pages = 0;
}