#include "manager/manager.h"

void initialize_disk_manager(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, Algorithm algorithm)
{
    initialize_virtual_memory(virtual_memory, "addresses.txt", "BACKING_STORE.bin");
    initialize_physical_memory(physical_memory, algorithm);
    initialize_tlb(tlb, virtual_memory, algorithm);
    initialize_page_table(page_table);
}

void read_virutual_memory_to_frame(VirtualMemory *virtual_memory, int page_number, int offset, int size, char *frame_data)
{
    char *data = readVirtualMemory(virtual_memory, page_number, offset, size);
    memcpy(frame_data, data, size);
    free(data);
}