#include <stdio.h>
#include <stdlib.h>
#include "memory_manager.h"
#include "page_table.h"
#include "tlb.h"
#include "utils/constants.h"
#include "disk_manager.h"
#include "algorithms/fifo.h"
#include "algorithms/lru.h"
#include "algorithms/optimal.h"

void initialize_memory_manager(TLBManager *tlb_manager, PageFaultManager *page_fault_manager) {
    tlb_manager->TLBhits = 0;
    tlb_manager->TLBmiss = false;
    page_fault_manager->pageFaults = 0;
    page_fault_manager->pageFault = false;
}

void handle_tlb_miss(TLB *tlb, PageTable *page_table, TLBManager *tlb_manager, PageFaultManager *page_fault_manager, uint32_t virtual_address) {
    const uint16_t PAGE_OFFSET_BITS = 8;
    const uint16_t PAGE_NUMBER_BITS = 16 - PAGE_OFFSET_BITS;

    uint16_t page_number = (virtual_address >> PAGE_OFFSET_BITS) & ((1 << PAGE_NUMBER_BITS) - 1);
    uint16_t offset = virtual_address & ((1 << PAGE_OFFSET_BITS) - 1);

    // Check if the page is in the TLB
    if (tlb_lookup(tlb, page_number) != -1) {
        tlb_manager->TLBhits++;
        tlb_manager->TLBmiss = false;
    }

    if(!tlb_manager->TLBmiss)
        return;

    // If the page is not in the TLB, check the page table
    if (page_table_lookup(page_table, page_number) != -1) {
        // If the page is in the page table, add it to the TLB
        tlb_add_entry(tlb, page_number, page_table->entries[page_number].frame_number);
    } else {
        // If the page is not in the page table, it is a page fault
        page_fault_manager->pageFaults++;
        page_fault_manager->pageFault = true;

        // Load the page from the disk into memory
        
    }
}