#include"main.h"
int translate_virtual_to_physical(TLB *tlb, PageTable *page_table, uint16_t virtual_address)
{
    uint8_t page_frame = (virtual_address >> 8) && PAGE_SIZE;
    
    if (tlb_lookup(tlb,page_frame) != -1) 
        return tlb_lookup(tlb,page_frame);
    
    return page_table_lookup(page_table, page_frame);
}
int main()
{
    return 0;
}


