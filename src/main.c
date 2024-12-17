#include "main.h"

int get_physical_address(int frame_number, int offset)
{
    return (int)frame_number * FRAME_SIZE + offset;
}

int get_offset(int virtual_address)
{
    return (int)virtual_address & ((1 << OFFSET_BITS) - 1);
}

int get_page_number(int virtual_address)
{
    return (int)(virtual_address >> OFFSET_BITS) & (PAGE_SIZE - 1);
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

    initialize_virtual_memory(virtual_memory, INPUT_FILE, BACKING_STORE_FILE);
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

    initialize_memory_manager(tlb_manager, page_fault_manager);
}

int get_frame_number(int virtual_address, int current_index)
{
    int page_number;
    int offset;
    int frame_number;

    page_number = get_page_number(virtual_address);
    offset = get_offset(virtual_address);

    frame_number = tlb_check(tlb, tlb_manager, virtual_address, current_index);

    // If TLB miss
    if (frame_number == -1)
    {

        // Check if the page is in the page table
        frame_number = page_table_check(page_table, page_fault_manager, virtual_address, current_index);

        // If Page table miss
        if (frame_number == -1)
        {
            frame_number = add_page_to_physical_memory(physical_memory, virtual_memory, frame_number, page_number);
            link_page_table_to_frame(page_table, page_number, frame_number);
        }
    }

    add_entry_to_tlb(tlb, page_number, frame_number, current_index);
    return frame_number;
}

void run(PhysicalMemory *physical_memory, int current_index)
{
    int virtual_address = virtual_memory->address[current_index];

    int page_number = get_page_number(virtual_address);
    int offset = get_offset(virtual_address);

    int frame_number = get_frame_number(virtual_address, current_index);
    // print fame_number and offset
    printf("Frame number: %d Offset: %d\n", frame_number, offset);
    int physical_address = get_physical_address(frame_number, offset);

    char data = (read_from_physical_memory(physical_memory, frame_number, offset)[0]);

    char output[100];
    sprintf(output, "Virtual address: %d Physical address: %d Value: %d", virtual_address, physical_address, data);
    write_to_output_file(OUTPUT_FILE, output);
}

int main()
{
    init();
    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        run(physical_memory, i);
    }

    printf("TLB hits: %d Page faults: %d\n", tlb_manager->TLBhits, page_fault_manager->pageFaults);
    return 0;
}
