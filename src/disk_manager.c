#include "disk_manager.h"

void initialize_disk_manager(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, Algorithm algorithm)
{
    initialize_virtual_memory(virtual_memory, "addresses.txt", "BACKING_STORE.bin");
    initialize_physical_memory(physical_memory, algorithm);
    initialize_tlb(tlb, algorithm);
    initialize_page_table(page_table);
}

void swap_in_page(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, uint32_t virtual_address){
    //const uint16_t PAGE_OFFSET_BITS = 8;
    //const uint16_t PAGE_NUMBER_BITS = 16 - PAGE_OFFSET_BITS;

    //uint16_t page_number = (virtual_address >> PAGE_OFFSET_BITS) & ((1 << PAGE_NUMBER_BITS) - 1);
    //uint16_t offset = virtual_address & ((1 << PAGE_OFFSET_BITS) - 1);

    char *data = malloc(FRAME_SIZE);
    memcpy(data, read_BACKINGSTORE(virtual_memory, virtual_address), FRAME_SIZE);   

    int physical_address = translate_address(page_table, virtual_address);
    write_to_physical_memory(physical_memory, physical_address, data, strlen(data));
}