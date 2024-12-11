#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <stdint.h>
#include "page_table.h"
#include "tlb.h"
#include "utils/constants.h"
#include "algorithms/algorithm.h"
#include "virtual_memory.h"
#include "physical_memory.h"

void initialize_disk_manager(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, Algorithm algorithm);

void swap_in_page(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, uint32_t virtual_address);

#endif // DISK_MANAGER_H
