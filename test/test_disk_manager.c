#include "../lib/manager/disk_manager.h"
#include "../lib/algorithms/algorithms.h"
#include "../lib/memory/physical_memory.h"

int main()
{
    VirtualMemory *virtual_memory;
    PhysicalMemory *physical_memory;
    TLB *tlb;
    PageTable *page_table;

    virtual_memory = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    // physical_memory = (PhysicalMemory *)malloc(sizeof(PhysicalMemory));
    tlb = (TLB *)malloc(sizeof(TLB));
    page_table = (PageTable *)malloc(sizeof(PageTable));

    initialize_disk_manager(virtual_memory, physical_memory, tlb, page_table, FIFO_ALGORITHM);
    add_page_to_physical_memory(physical_memory, virtual_memory, 0, 1);
    char *result = read_from_physical_memory(physical_memory, 0, 0);
    printf("Result: %s\n", result);

}