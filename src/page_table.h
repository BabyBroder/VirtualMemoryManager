/**
 * @file page_table.h
 * @brief Defines structures for page table entries and the page table.
*/

#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include <stdint.h>
#include <stdbool.h>
#include "utils/constants.h"
#include "physical_memory.h"


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
typedef struct {
    uint16_t frame_number; /**< Frame number in physical memory. */
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

typedef struct {
    PageTableEntry *entries; /**< Array of page table entries. */
    size_t num_pages;        /**< Total number of pages. */
} PageTable;

/**
 * Initializes the page table.
 *
 * @param page_table A pointer to the PageTable structure to be initialized.
 */
void initialize_page_table(PageTable *page_table);

/**
 * Looks up the page table for a given page number.
 *
 * @param page_table A pointer to the PageTable structure.
 * @param page_number The page number to look up.
 * @return The frame number corresponding to the page number, or -1 if the page is not found.
 */
int page_table_lookup(PageTable *page_table, uint16_t page_number);

/**
 * Translates a logical page number to a frame number.
 *
 * @param page_table A pointer to the PageTable structure.
 * @param virtual_address The virtual address to be translated.
 * @return The frame number corresponding to the virtual address, or -1 if the page is not valid (i.e., a page fault).
 */
int translate_address(PageTable *page_table, uint32_t virtual_address);

/**
 * Updates the page table when a page is loaded into memory.
 *
 * @param page_table A pointer to the PageTable structure.
 * @param page_number The page number to be updated.
 * @param frame_number The frame number to be associated with the page number.
 */
void update_page_table(PageTable *page_table, uint16_t page_number, uint16_t frame_number);

/**
 * Gets the page by page number.
 *
 * @param page_table A pointer to the PageTable structure.
 * @param page_id The page number to retrieve.
 * @return A pointer to the Frame structure corresponding to the page number.
 */
Frame *get_page(PageTable *page_table, uint16_t page_id);

/**
 * Loads a page into memory.
 *
 * @param physical_memory A pointer to the PhysicalMemory structure.
 * @param page_table A pointer to the PageTable structure.
 * @param page_id The page number to be loaded.
 * @param data A pointer to the data to be loaded into the page.
 * @param current_index The current index in the physical memory where the page will be loaded.
 */
void load_page(PhysicalMemory *physical_memory, PageTable *page_table, uint16_t page_id, const char *data, int current_index);

/**
 * Cleans up resources allocated for the page table.
 *
 * @param physical_memory A pointer to the PhysicalMemory structure associated with the page table.
 * @param page_table A pointer to the PageTable structure to be freed.
 */
void free_page_table(PhysicalMemory* physical_memory, PageTable *page_table) ;

#endif // PAGE_TABLE_H
