/**
 * @file memory_manager.h
 * @brief Header file for memory management components including TLB and Page Fault management.
 */

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdint.h>
#include <stdbool.h>
#include "page_table.h"
#include "tlb.h"

/**
 * @struct TLBManager
 * @brief Structure to manage TLB hits and misses.
 * 
 * @var TLBManager::TLBhits
 * Number of TLB hits.
 * 
 * @var TLBManager::TLBmiss
 * Boolean flag indicating a TLB miss.
 */
typedef struct {
    int TLBhits; /**< Total number of TLB hits. */
} TLBManager;

/**
 * @struct PageFaultManager
 * @brief Structure to manage page faults.
 * 
 * @var PageFaultManager::pageFaults
 * Number of page faults.
 * 
 * @var PageFaultManager::pageFault
 * Boolean flag indicating a page fault.
 */
typedef struct {
    int pageFaults; /**< Total number of page faults. */
} PageFaultManager;

/**
 * @brief Initializes memory management components.
 * 
 * @param tlb_manager Pointer to TLBManager structure.
 * @param page_fault_manager Pointer to PageFaultManager structure.
 */
void initialize_memory_manager(TLBManager *tlb_manager, PageFaultManager *page_fault_manager);

/**
 * @brief Handles a TLB miss.
 * 
 * @param tlb Pointer to TLB structure.
 * @param page_table Pointer to PageTable structure.
 * @param tlb_manager Pointer to TLBManager structure.
 * @param page_fault_manager Pointer to PageFaultManager structure.
 * @param virtual_address The virtual address that caused the TLB miss.
 * @param current_index The current index in the TLB.
 */
bool tlb_check(TLB *tlb, PageTable *page_table, TLBManager *tlb_manager, PageFaultManager *page_fault_manager, uint32_t virtual_address, int current_index);

bool page_table_check(TLB *tlb, PageTable *page_table, TLBManager *tlb_manager, PageFaultManager *page_fault_manager, uint32_t virtual_address, int current_index);

#endif // MEMORY_MANAGER_H