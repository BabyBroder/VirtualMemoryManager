#include "../../lib/manager/manager.h"

void initialize_memory_manager(TLBManager *tlb_manager, PageFaultManager *page_fault_manager)
{
    tlb_manager->TLBhits = 0;
    page_fault_manager->pageFaults = 0;
}

int tlb_check(TLB *tlb, TLBManager *tlb_manager, uint32_t virtual_address, int current_index)
{
    const uint16_t PAGE_OFFSET_BITS = 8;
    const uint16_t PAGE_NUMBER_BITS = 16 - PAGE_OFFSET_BITS;
    uint16_t page_number = (virtual_address >> PAGE_OFFSET_BITS) & ((1 << PAGE_NUMBER_BITS) - 1);

    // Check if the page is in the TLB
    int frame_number = tlb_lookup(tlb, page_number);
    if (frame_number != -1)
    {
        tlb_manager->TLBhits++;
        return frame_number;
    }
    else
        return -1;
}

int page_table_check(PageTable *page_table, PageFaultManager *page_fault_manager, uint32_t virtual_address, int current_index)
{
    const uint16_t PAGE_OFFSET_BITS = 8;
    const uint16_t PAGE_NUMBER_BITS = 16 - PAGE_OFFSET_BITS;
    uint16_t page_number = (virtual_address >> PAGE_OFFSET_BITS) & ((1 << PAGE_NUMBER_BITS) - 1);

    int frame_number = page_table_lookup(page_table, page_number);
    if (frame_number == -1)
    {
        // If the page is not in the page table, it is a page fault
        page_fault_manager->pageFaults++;
        return -1;
    }

    return frame_number;
}