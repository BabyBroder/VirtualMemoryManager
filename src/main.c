#include "main.h"

uint16_t get_physical_address(uint8_t frame_number, uint8_t offset)
{
    return (uint16_t)frame_number * FRAME_SIZE + offset;
}

uint8_t get_offset(int virtual_address)
{
    return (uint8_t)virtual_address & ((1 << OFFSET_BITS) - 1);
}

uint8_t get_page_number(int virtual_address)
{
    return (uint8_t)(virtual_address >> OFFSET_BITS) & (PAGE_SIZE - 1);
}

void init()
{
    virtual_memory = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    physical_memory = (PhysicalMemory *)malloc(sizeof(PhysicalMemory));
    tlb = (TLB *)malloc(sizeof(TLB));
    page_table = (PageTable *)malloc(sizeof(PageTable));

    if (virtual_memory == NULL || physical_memory == NULL || tlb == NULL || page_table == NULL)
    {
        printf("Failed to allocate memory for virtual memory, physical memory, TLB, or page table\n");
        exit(EXIT_FAILURE);
    }

    initialize_virtual_memory(virtual_memory, BACKING_STORE_FILE, INPUT_FILE);
    initialize_physical_memory(physical_memory, algorithm);
    initialize_tlb(tlb, virtual_memory, algorithm);
    initialize_page_table(page_table);

    tlb_manager = (TLBManager *)malloc(sizeof(TLBManager));
    page_fault_manager = (PageFaultManager *)malloc(sizeof(PageFaultManager));

    if (tlb_manager == NULL || page_fault_manager == NULL)
    {
        printf("Failed to allocate memory for TLB manager or page fault manager\n");
        exit(EXIT_FAILURE);
    }
}

uint8_t get_frame_number(int virtual_address, int current_index)
{
    uint8_t page_number;
    uint8_t offset;
    uint8_t frame_number;

    frame_number = tlb_check(tlb, tlb_manager, virtual_address, current_index);

    // If TLB miss
    if (frame_number == -1)
    {

        // Check if the page is in the page table
        frame_number = page_table_check(page_table, page_fault_manager, virtual_address, current_index);

        // If Page table miss
        if (frame_number == -1)
        {

            int *page_number_and_offset = get_page_number_and_offset(virtual_address);
            page_number = page_number_and_offset[0];
            offset = page_number_and_offset[1];
            char *frame_data = readVirtualMemory(virtual_memory, page_number, offset, PAGE_SIZE);

            frame_number = find_free_frame(physical_memory);
            link_page_table_to_frame(page_table, page_number, frame_number);
        }
    }

    add_entry_to_tlb(tlb, page_number, frame_number, current_index);
    return frame_number;
}

void write_to_physical_memory(PhysicalMemory *physical_memory, int current_index)
{
    uint16_t virutal_address = virtual_memory->address[current_index];
    
    uint8_t page_number = get_page_number(virutal_address);
    uint8_t offset = get_offset(virutal_address);

    uint8_t frame_number = get_frame_number(virutal_address, current_index);
    uint16_t physical_address = get_physical_address(frame_number, offset);

    // Add data from the specific page number into frame number
    add_page_to_physical_memory(physical_memory, virtual_memory, frame_number, page_number);
}

int main()
{

    return 0;
}
