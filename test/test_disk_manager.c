#include "../src/main.h"

int main()
{
    VirtualMemory *virtual_memory;
    PhysicalMemory *physical_memory;
    TLB *tlb;
    PageTable *page_table;

    virtual_memory = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    physical_memory = (PhysicalMemory *)malloc(sizeof(PhysicalMemory));
    tlb = (TLB *)malloc(sizeof(TLB));
    page_table = (PageTable *)malloc(sizeof(PageTable));
    if(virtual_memory == NULL || physical_memory == NULL || tlb == NULL || page_table == NULL)
    {
        perror("Error allocating memory");
        exit(1);
    }
    initialize_disk_manager(virtual_memory, physical_memory, tlb, page_table, FIFO_ALGORITHM);
    add_page_to_physical_memory(physical_memory, virtual_memory, 0, 1);
    char *result = read_from_physical_memory(physical_memory, 0, 0);
    printf("Result: %s\n", result);

}