#include "tlb.h"
#include <stdlib.h>
#include <string.h>

static TLBEntry *tlb = NULL;
static int tlb_size = 0;
static int next_entry_index = 0; 

void initialize_tlb(int size) {}

int lookup_tlb(int virtual_address) {}

void update_tlb(int virtual_address, int physical_address) {}

void invalidate_tlb_entry(int virtual_address) {}

void clear_tlb() {}

void free_tlb() {}

