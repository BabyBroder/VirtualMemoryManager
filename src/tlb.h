#ifndef TLB_H
#define TLB_H

#include <stdint.h>
#include <stdbool.h>
#include "page_table.h"

// Maximum number of entries in the TLB
#define TLB_SIZE 16

// Structure for a single TLB entry
typedef struct {
    uint16_t page_number; // Logical page number
    uint16_t frame_number; // Physical frame number
    bool valid;            // Valid bit to indicate if the entry is valid
} TLBEntry;

// Structure for the TLB
typedef struct {
    TLBEntry entries[TLB_SIZE]; // Array of TLB entries
    int next_replace_index;     // Index for replacement (FIFO or other policy)
} TLB;

// Initializes the TLB
void initialize_tlb(TLB *tlb);

// Looks up the TLB for a given page number
// Returns the frame number on a hit, -1 on a miss
int tlb_lookup(TLB *tlb, uint16_t page_number);

// Adds an entry to the TLB (replaces an existing one if necessary)
void tlb_add_entry(TLB *tlb, uint16_t page_number, uint16_t frame_number);

// Prints the contents of the TLB (for debugging or logging)
void print_tlb(const TLB *tlb);

#endif // TLB_H
