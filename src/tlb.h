/**
 * @file tlb.h
 * @brief Header file for the Translation Lookaside Buffer (TLB) management.
 *
 * This file contains the definitions and function prototypes for managing
 * the TLB in a virtual memory system.
 */

#ifndef TLB_H
#define TLB_H

#include <stdint.h>
#include <stdbool.h>
#include "page_table.h"
#include "algorithms/algorithm.h"
#include "utils/constants.h"
#include "virtual_memory.h"


/**
 * @struct TLBEntry
 * @brief Represents an entry in the TLB.
 *
 * This structure represents an entry in the TLB, containing the logical
 * page number, physical frame number, and a valid bit.
 */
typedef struct {
    uint16_t page_number; /**< Logical page number */
    uint16_t frame_number; /**< Physical frame number */
    bool valid;            /**< Valid bit to indicate if the entry is valid */
} TLBEntry;


/**
 * @struct TLB
 * @brief Represents the Translation Lookaside Buffer.
 *
 * This structure represents the TLB, containing an array of TLB entries
 * and the replacement algorithm used.
 */
typedef struct {
    TLBEntry entries[TLB_ENTRIES]; /**< Array of TLB entries */
    int replacement;     /**< Index for replacement (FIFO = 0, LRU = 1, OPT = 2) */
    Algorithm algorithm; /**< Algorithm used for replacement */
    AlgorithmStruct algorithm_struct; /**< Structure for the algorithm */
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
void initialize_tlb(TLB *tlb, VirtualMemory *virtual_memory ,Algorithm algorithm);


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
int choose_entry_to_replace(TLB *tlb, uint16_t page_number, uint16_t frame_number, int current_index);

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
void tlb_add_entry(TLB *tlb, uint16_t page_number, uint16_t frame_number, int current_index);


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
int tlb_lookup(TLB *tlb, uint16_t page_number);

/**
 * @brief Prints the contents of the TLB.
 *
 * This function prints the contents of the TLB to the console.
 *
 * @param tlb Pointer to the TLB structure.
 */
void print_tlb(const TLB *tlb);

#endif // TLB_H
