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

/**
 * @struct TLBEntry
 * @brief Structure for a single TLB entry.
 *
 * This structure represents a single entry in the TLB, containing the
 * logical page number, physical frame number, and a valid bit.
 */
typedef struct {
    uint16_t page_number; /**< Logical page number */
    uint16_t frame_number; /**< Physical frame number */
    bool valid;            /**< Valid bit to indicate if the entry is valid */
} TLBEntry;

/**
 * @struct TLB
 * @brief Structure for the TLB.
 *
 * This structure represents the TLB, containing an array of TLB entries,
 * the replacement policy, and the algorithm used for replacement.
 */
typedef struct {
    TLBEntry entries[TLB_ENTRIES]; /**< Array of TLB entries */
    int replacement;     /**< Index for replacement (FIFO = 0, LRU = 1, OPT = 2) */
    Algorithm algorithm; /**< Algorithm used for replacement */
    AlgorithmStruct algorithm_struct; /**< Structure for the algorithm */
} TLB;

/**
 * @brief Initializes the TLB.
 *
 * This function initializes the TLB with the specified replacement algorithm.
 *
 * @param tlb Pointer to the TLB structure to initialize.
 * @param algorithm The replacement algorithm to use.
 */
void initialize_tlb(TLB *tlb, Algorithm algorithm);

/**
 * @brief Chooses an entry to replace in the TLB.
 *
 * This function selects an entry in the TLB to replace based on the
 * specified replacement algorithm.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The logical page number to add.
 * @param frame_number The physical frame number to add.
 * @param current_index The current index in the TLB.
 * @return The index of the entry to replace.
 */
int choose_entry_to_replace(TLB *tlb, uint16_t page_number, uint16_t frame_number, int current_index);

/**
 * @brief Adds an entry to the replacement structure.
 *
 * This function adds an entry to the replacement structure based on the
 * specified replacement algorithm.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The logical page number to add.
 * @param frame_number The physical frame number to add.
 * @param current_index The current index in the TLB.
 * @return True if the entry was added successfully, false otherwise.
 */
bool add_entry_to_replacment(TLB *tlb, uint16_t page_number, uint16_t frame_number, int current_index);

/**
 * @brief Adds an entry to the TLB.
 *
 * This function adds an entry to the TLB, replacing an existing one if
 * necessary based on the specified replacement algorithm.
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
 * This function searches the TLB for the specified logical page number.
 * If a match is found, it returns the corresponding physical frame number.
 * If no match is found, it returns -1.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The logical page number to look up.
 * @return The physical frame number on a hit, -1 on a miss.
 */
int tlb_lookup(TLB *tlb, uint16_t page_number);

/**
 * @brief Prints the contents of the TLB.
 *
 * This function prints the contents of the TLB for debugging or logging
 * purposes.
 *
 * @param tlb Pointer to the TLB structure.
 */
void print_tlb(const TLB *tlb);

#endif // TLB_H
