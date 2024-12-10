#include <stdio.h>
#include <stdlib.h>
#include "disk_manager.h"
#include "page_table.h"
#include "memory_manager.h"

// Initializes the disk with empty pages
void initialize_disk(Disk *disk) {}

// Reads a page from the disk
// Returns the data of the page or NULL if the page is not in the disk
char* read_page_from_disk(Disk *disk, uint16_t page_id) {}

// Writes a page to the disk
void write_page_to_disk(Disk *disk, uint16_t page_id, const char *data) {}
