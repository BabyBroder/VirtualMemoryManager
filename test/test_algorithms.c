#include "algorithms/algorithms.h"

//  Different size for address
#undef ADDRESS_SIZE
#define ADDRESS_SIZE 30

void add_to_fifo(FIFO *fifo, int value)
{
    printf("Adding %d to FIFO\n", value);
    fifo_add_page(fifo, value);
    print_fifo(fifo);
}

void testFIFO(int size)
{
    printf("=====================================\n");
    printf("Testing FIFO\n");
    FIFO *fifo;
    fifo = (FIFO *)malloc(sizeof(FIFO));
    initialize_fifo(fifo, size);
    printf("FIFO initialized with size: %d\n", size);

    int values[] = {1, 2, 3, 2, 6, 4, 10, 8, 12, 4};
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
        add_to_fifo(fifo, values[i]);
    }

    printf("Final FIFO state: ");
    print_fifo(fifo);
    printf("=====================================\n");
    free_fifo(fifo);
}

void add_to_lru(LRU *lru, int value)
{
    printf("Adding %d to LRU\n", value);
    lru_add_page(lru, value);
    print_lru(lru);
}

void testLRU(int size)
{
    LRU *lru;
    lru = (LRU *)malloc(sizeof(LRU));
    printf("LRU initialized with size: %d\n", size);
    initialize_lru(lru, size);

    int values[] = {1, 2, 3, 2, 6, 4, 10, 8, 12, 4};
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
    {
        add_to_lru(lru, values[i]);
    }

    printf("Final LRU state: ");
    print_lru(lru);
    printf("=====================================\n");
    free_lru(lru);
}

void add_to_OPT(Optimal *optimal, int page, int current_index)
{
    printf("Adding %d to OPT\n", page);
    optimal_add_page(optimal, page, current_index);
    print_optimal(optimal);
}

void init_OPT(Optimal *structure, VirtualMemory *virtual_memory, int capacity)
{

    if (structure->initialized)
    {
        fprintf(stderr, "Error: Optimal already initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (capacity <= 0)
    {
        fprintf(stderr, "Optimal Error: Invalid capacity value!\n");
        exit(EXIT_FAILURE);
    }

    structure->capacity = capacity;
    structure->size = 0;

    structure->pages = (int *)malloc(structure->capacity * sizeof(int));
    structure->future_usage = (int *)malloc(ADDRESS_SIZE * sizeof(int));
    structure->initialized = true;

    if (!structure->pages || !structure->future_usage)
    {
        perror("Optimal Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->capacity; i++)
        structure->pages[i] = -1;

    // Write address to future_usage
    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        int page_number = virtual_memory->address[i];
        structure->future_usage[i] = page_number;
    }
}

void testOPT(VirtualMemory *virtual_memory)
{
    Optimal *optimal;
    optimal = (Optimal *)malloc(sizeof(Optimal));

    // True implementation
    //initialize_optimal(optimal, virtual_memory, 5); // Assuming the third argument is the number of pages
    
    //  In test_algorithms.c, we will assume the address in addresses.txt as a page_number for checking the optimal algorithm not for logic implementation
    init_OPT(optimal, virtual_memory, 5);
    printf("Optimal initialized\n");
    
    printf("Capacity: %d\n", optimal->capacity);
    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        add_to_OPT(optimal, virtual_memory->address[i], i);
    }

    printf("Final OPT state: ");
    print_optimal(optimal);
    printf("=====================================\n");
    free_optimal(optimal);
}

int main()
{
    printf("=====================================\n");
    printf("Address size: %d\n", ADDRESS_SIZE);
    testFIFO(3);
    testLRU(3);

    VirtualMemory *virtual_memory = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    initialize_virtual_memory(virtual_memory, "./addresses.txt", "./BACKING_STORE.bin");
    printf("Virtual memory initialized\n");
    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        printf("%d ", virtual_memory->address[i]);
    }
    printf("\n");
    printf("Virtual memory address printed\n");
    printf("=====================================\n");
    testOPT(virtual_memory);
    return 0;
}
