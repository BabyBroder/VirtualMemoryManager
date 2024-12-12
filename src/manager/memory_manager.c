#include "../../lib/manager/manager.h"

/**
 * @brief Initializes the memory manager with the provided TLB and page fault manager.
 *
 * @param tlb_manager Pointer to TLBManager structure.
 * @param page_fault_manager Pointer to PageFaultManager structure.
 */
void initialize_memory_manager(TLBManager *tlb_manager, PageFaultManager *page_fault_manager)
{
    tlb_manager->TLBhits = 0;
    page_fault_manager->pageFaults = 0;
}

/**
 * @brief Checks if the virtual address is in the TLB.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_table Pointer to the PageTable structure.
 * @param tlb_manager Pointer to the TLBManager structure.
 * @param page_fault_manager Pointer to the PageFaultManager structure.
 * @param virtual_address The virtual address to check.
 * @param current_index The current index in the TLB.
 * @return True if the virtual address is in the TLB, false otherwise.
 */
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

/**
 * @brief Checks if the virtual address is in the page table.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_table Pointer to the PageTable structure.
 * @param tlb_manager Pointer to the TLBManager structure.
 * @param page_fault_manager Pointer to the PageFaultManager structure.
 * @param virtual_address The virtual address to check.
 * @param current_index The current index in the TLB.
 * @return True if the virtual address is in the page table, false otherwise.
 */
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