/**
 * @file memory_manager.h
 * @brief Header file for memory management components including TLB and Page Fault management.
 */

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "../structure/structure.h"

// #include "page_table.h"
// #include "tlb.h"

/**
 * @struct TLBManager
 * @brief Structure to manage TLB hits.
 *
 * @var TLBManager::TLBhits
 * Number of TLB hits.
 */
typedef struct
{
    int TLBhits; /**< Total number of TLB hits. */
} TLBManager;

/**
 * @struct PageFaultManager
 * @brief Structure to manage page faults.
 *
 * @var PageFaultManager::pageFaults
 * Number of page faults.
 */
typedef struct
{
    int pageFaults; /**< Total number of page faults. */
} PageFaultManager;

/**
 * @brief Initializes the memory manager with the provided TLB and page fault manager.
 *
 * @param tlb_manager Pointer to TLBManager structure.
 * @param page_fault_manager Pointer to PageFaultManager structure.
 */
int initialize_memory_manager(TLBManager *tlb_manager, PageFaultManager *page_fault_manager);

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
int tlb_check(TLB *tlb, TLBManager *tlb_manager, uint32_t virtual_address, int current_index);

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
int page_table_check(PageTable *page_table, PageFaultManager *page_fault_manager, uint32_t virtual_address, int current_index);

#endif // MEMORY_MANAGER_H