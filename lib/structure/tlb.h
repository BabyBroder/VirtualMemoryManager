/**
 * @file tlb.h
 * @brief Header file for the Translation Lookaside Buffer (TLB) management.
 *
 * This file contains the definitions and function prototypes for managing
 * the TLB in a virtual memory system.
 */

#ifndef TLB_H
#define TLB_H

#include "../memory/memory.h"

/**
 * @struct TLBEntry
 * @brief Represents an entry in the Translation Lookaside Buffer (TLB).
 *
 * This structure is used to map a logical page number to a physical frame number
 * and includes a valid bit to indicate if the entry is currently valid.
 *
 * @var TLBEntry::page_number
 * Logical page number.
 *
 * @var TLBEntry::frame_number
 * Physical frame number.
 *
 * @var TLBEntry::valid
 * Valid bit to indicate if the entry is valid.
 */
typedef struct
{
    int page_number;  /**< Logical page number */
    int frame_number; /**< Physical frame number */
    bool valid;       /**< Valid bit to indicate if the entry is valid */
} TLBEntry;

/**
 * @struct TLB
 * @brief Represents a Translation Lookaside Buffer (TLB).
 *
 * This structure defines a TLB which is used to improve the speed of virtual address translation.
 *
 * @var TLB::entries
 * Array of TLB entries.
 *
 * @var TLB::replacement
 * Index for replacement policy (FIFO = 0, LRU = 1, OPT = 2).
 *
 * @var TLB::algorithm
 * Algorithm used for replacement.
 *
 * @var TLB::algorithm_struct
 * Structure for the algorithm.
 *
 * @var TLB::initialized
 * Flag to indicate if the TLB is initialized.
 */
typedef struct
{
    TLBEntry entries[TLB_ENTRIES];    /**< Array of TLB entries */
    int replacement;                  /**< Index for replacement (FIFO = 0, LRU = 1, OPT = 2) */
    Algorithm algorithm;              /**< Algorithm used for replacement */
    AlgorithmStruct algorithm_struct; /**< Structure for the algorithm */
    bool initialized;                 /**< Flag to indicate if the TLB is initialized */
} TLB;

/**
 * @brief Initializes the TLB with the specified virtual memory and replacement algorithm.
 *
 * This function initializes the TLB with the specified virtual memory and
 * replacement algorithm. The TLB is initialized with all entries marked as
 * invalid.
 *
 * @param tlb Pointer to the TLB structure.
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param algorithm The replacement algorithm to use.
 */
void initialize_tlb(TLB *tlb, VirtualMemory *virtual_memory, Algorithm algorithm);

/**
 * @brief Chooses an entry to replace in the TLB.
 *
 * This function selects an entry in the TLB to replace based on the
 * specified replacement algorithm.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The logical page number to replace.
 * @param frame_number The physical frame number to replace.
 * @param current_index The current index in the TLB.
 * @return The index of the entry to replace.
 */
int choose_entry_to_replace(TLB *tlb, int page_number, int frame_number, int current_index);

/**
 * @brief Adds an entry to the TLB.
 *
 * This function adds an entry to the TLB at the specified index.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The logical page number to add.
 * @param frame_number The physical frame number to add.
 * @param current_index The current index in the TLB.
 */
int add_entry_to_tlb(TLB *tlb, int page_number, int frame_number, int current_index);

/**
 * @brief Looks up the TLB for a given page number.
 *
 * This function looks up the TLB for a given page number and returns the
 * corresponding frame number if the entry is valid.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The page number to look up.
 * @return The frame number corresponding to the page number, or -1 if the entry is not valid.
 */
int tlb_lookup(TLB *tlb, int page_number);

/**
 * @brief Prints the contents of the TLB.
 *
 * This function prints the contents of the TLB to the console.
 *
 * @param tlb Pointer to the TLB structure.
 */
void print_tlb(const TLB *tlb);

#endif // TLB_H
