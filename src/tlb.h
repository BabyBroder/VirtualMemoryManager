#ifndef TLB_H
#define TLB_H

void initialize_tlb();
int lookup_tlb(int virtual_address);
void update_tlb(int virtual_address, int physical_address);
void invalidate_tlb_entry(int virtual_address);

#endif // TLB_H
