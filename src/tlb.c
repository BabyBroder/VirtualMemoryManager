#include <stdio.h>
#include <stdlib.h>
#include "tlb.h"
#include "page_table.h"
#include "utils/constants.h"

void initialize_tlb(TLB *tlb) {}

int tlb_lookup(TLB *tlb, uint16_t page_number) {}

void tlb_add_entry(TLB *tlb, uint16_t page_number, uint16_t frame_number) {}

void print_tlb(const TLB *tlb) {}
