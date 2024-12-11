#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk_manager.h"
#include "page_table.h"
#include "tlb.h"
#include "utils/constants.h"
#include "memory_manager.h"

void initialize_disk_manager(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, Algorithm algorithm)
{
    initialize_virtual_memory(virtual_memory, "addresses.txt", "BACKING_STORE.bin");
    initialize_physical_memory(physical_memory, algorithm);
    initialize_tlb(tlb);
    initialize_page_table(page_table);
}
