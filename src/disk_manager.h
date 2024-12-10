#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <stdint.h>
#include "page_table.h"
#include "tlb.h"
#include "utils/constants.h"
#include "memory_manager.h"

// Size of the disk (number of pages it can hold)
#define DISK_SIZE (PAGE_TABLE_ENTRIES)

// Disk data structure
typedef struct {
    char data[DISK_SIZE][PAGE_SIZE]; // Disk storage for pages
} Disk;

// Initializes the disk
void initialize_disk(Disk *disk);

// Reads a page from the disk
// Returns the data of the page or NULL if the page is not in the disk
char* read_page_from_disk(Disk *disk, uint16_t page_id);

// Writes a page to the disk
void write_page_to_disk(Disk *disk, uint16_t page_id, const char *data);

// Swaps in a page from the disk into memory
void swap_in_page(Disk *disk, PageTable *page_table, TLB *tlb, int page_number, char *page_data);

// Swaps out a page from memory to disk
void swap_out_page(Disk *disk, PageTable *page_table, TLB *tlb, int page_number);

// Checks if a page is on the disk
bool is_page_on_disk(Disk *disk, int page_number);

// Checks if the disk is empty
bool is_disk_empty(Disk *disk);

#endif // DISK_MANAGER_H
