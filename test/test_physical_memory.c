#include "../src/main.h"

typedef struct
{
    uint16_t frame_number;
    uint16_t page_number;
} PhysicalMemoryInput;

void print_physical_memory_data(PhysicalMemory *physical_memory)
{
    for (int i = 0; i < 256 * 10; i++)
    {
        printf("%02x ", (unsigned char)read_from_physical_memory(physical_memory, i, 0)[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }
}

void print_physical_memory(PhysicalMemory *physical_memory)
{
    for (int i = 0; i < physical_memory->nums_frames; i++)
    {
        printf("Frame %d: %d\n", i, physical_memory->frames[i].page_number);
    }
}

void print_physical_memory_input(PhysicalMemoryInput *test)
{
    for (int i = 0; i < 18; i++)
    {
        printf("Frame %d: %d\n", test[i].frame_number, test[i].page_number);
    }
}

void add_page(PhysicalMemory *physical_memory, VirtualMemory *virtualMemory, PhysicalMemoryInput *test)
{
    printf("=====================================\n");
    printf("Physical Memory INPUT\n\n");
    print_physical_memory_input(test);
    for (uint16_t i = 0; i < 18; i++)
    {
        add_page_to_physical_memory(physical_memory, virtualMemory, test[i].frame_number, test[i].page_number);

        printf("=====================================\n");
        printf("Physical Memory FiFo\n");
        print_physical_memory(physical_memory);
    }
}

int main()
{
    VirtualMemory *virtualMemory = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    initialize_virtual_memory(virtualMemory, "addresses.txt", "BACKING_STORE.bin");

    PhysicalMemoryInput test[18];
    test[0].frame_number = 10;
    test[0].page_number = 10;
    for (uint16_t i = 1; i < 18; i++)
    {
        test[i].frame_number = i;
        test[i].page_number = i;
    }
    test[17].frame_number = 10;
    test[17].page_number = 10;

    PhysicalMemory *physicalMemoryFiFo = (PhysicalMemory *)malloc(sizeof(PhysicalMemory));
    PhysicalMemory *physicalMemoryLRU = (PhysicalMemory *)malloc(sizeof(PhysicalMemory));

    initialize_physical_memory(physicalMemoryFiFo, FIFO_ALGORITHM);
    initialize_physical_memory(physicalMemoryLRU, LRU_ALGORITHM);

    add_page(physicalMemoryFiFo, virtualMemory, test);

    return 0;
}