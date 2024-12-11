#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdint.h>
#include <stdbool.h>
#include "page_table.h"
#include "tlb.h"

typedef struct{
    int TLBhits;
    bool TLBmiss;
} TLBManager;

typedef struct{
    int pageFaults;
    bool pageFault;
} PageFaultManager;

// Function to initialize memory management components
void initialize_memory_manager(TLBManager *tlb_manager, PageFaultManager *page_fault_manager);

// Function to handle a TLB miss
void handle_tlb_miss(TLB *tlb, PageTable *page_table, TLBManager *tlb_manager, PageFaultManager *page_fault_manager, uint32_t virtual_address, int current_index);

#endif // MEMORY_MANAGER_H
