#include "../../lib/manager/manager.h"

void initialize_memory_manager(TLBManager *tlb_manager, PageFaultManager *page_fault_manager)
{
    tlb_manager->TLBhits = 0;
    page_fault_manager->pageFaults = 0;
}

bool tlb_check(TLB *tlb, PageTable *page_table, TLBManager *tlb_manager, PageFaultManager *page_fault_manager, uint32_t virtual_address, int current_index)
{
    const uint16_t PAGE_OFFSET_BITS = 8;
    const uint16_t PAGE_NUMBER_BITS = 16 - PAGE_OFFSET_BITS;
    uint16_t page_number = (virtual_address >> PAGE_OFFSET_BITS) & ((1 << PAGE_NUMBER_BITS) - 1);

    // Check if the page is in the TLB
    if (tlb_lookup(tlb, page_number) != -1)
    {
        tlb_manager->TLBhits++;
        return true;
    }
    else
        return false;
}

bool page_table_check(TLB *tlb, PageTable *page_table, TLBManager *tlb_manager, PageFaultManager *page_fault_manager, uint32_t virtual_address, int current_index)
{
    const uint16_t PAGE_OFFSET_BITS = 8;
    const uint16_t PAGE_NUMBER_BITS = 16 - PAGE_OFFSET_BITS;
    uint16_t page_number = (virtual_address >> PAGE_OFFSET_BITS) & ((1 << PAGE_NUMBER_BITS) - 1);

    if (page_table_lookup(page_table, page_number) == -1)
    {
        // If the page is not in the page table, it is a page fault
        page_fault_manager->pageFaults++;
        return false;
    }

    return true;
}