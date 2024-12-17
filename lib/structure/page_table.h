/**
 * @file page_table.h
 * @brief Defines structures for page table entries and the page table.
 */

#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include "../memory/memory.h"

/**
 * @struct PageTableEntry
 * @brief Represents an entry in the page table.
 *
 * @var PageTableEntry::frame_number
 * Frame number in physical memory.
 *
 * @var PageTableEntry::valid
 * Valid bit to indicate if the page is in memory.
 */
typedef struct
{
    int frame_number; /**< Frame number in physical memory. */
    bool valid;            /**< Valid bit to indicate if the page is in memory. */
} PageTableEntry;

/**
 * @struct PageTable
 * @brief Represents the page table.
 *
 * @var PageTable::entries
 * Array of page table entries.
 *
 * @var PageTable::num_pages
 * Total number of pages.
 */
// Structure for a page table entry

typedef struct
{
    PageTableEntry *entries; /**< Array of page table entries. */
    size_t num_pages;        /**< Total number of pages. */
    bool initialized;        /**< Flag to indicate if the page table is initialized. */
} PageTable;

/**
 * Initializes the page table with the given number of pages.
 *
 * @param page_table A pointer to the PageTable structure.
 */
void initialize_page_table(PageTable *page_table);

/**
 * Looks up the page table for a given page number.
 *
 * @param page_table A pointer to the PageTable structure.
 * @param page_number The page number to look up.
 * @return The frame number corresponding to the page number, or -1 if the page is not found.
 */
int page_table_lookup(PageTable *page_table, int page_number);

/**
 * Updates the page table when a page is loaded into memory.
 *
 * @param page_table A pointer to the PageTable structure.
 * @param page_number The page number to be updated.
 * @param frame_number The frame number to be associated with the page number.
 */
void link_page_table_to_frame(PageTable *page_table, int page_number, int frame_number);

/**
 * Cleans up resources allocated for the page table.
 * @param page_table A pointer to the PageTable structure to be freed.
 */
void free_page_table(PageTable *page_table);

#endif // PAGE_TABLE_H
