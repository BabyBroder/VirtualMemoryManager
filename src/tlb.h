#ifndef TLB_H
#define TLB_H

#include <stdbool.h>

typedef struct {
    int virtual_address;
    int physical_address;
    bool valid;
} TLBEntry;

void initialize_tlb(int tlb_size);

int lookup_tlb(int virtual_address);

void update_tlb(int virtual_address, int physical_address);

void invalidate_tlb_entry(int virtual_address);

void clear_tlb();

#endif // TLB_H
