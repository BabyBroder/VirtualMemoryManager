#include "algorithms/algorithms.h"

void initialize_optimal(Optimal *structure, VirtualMemory *virtual_memory, int capacity)
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
        int page_number = virtual_memory->address[i] >> 8 & 0xFF;
        structure->future_usage[i] = page_number;
    }
}

int optimal_choose_page_to_replace(Optimal *structure, int current_index)
{

    if (!structure)
    {
        fprintf(stderr, "Error: OPT not initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (structure->size == 0)
    {
        fprintf(stderr, "Optimal Error: No pages to replace (memory is empty)!\n");
        exit(EXIT_FAILURE);
    }

    int index = -1, farthest = -1;
    for (int i = 0; i < structure->capacity; i++)
    {
        int dist = -1;
        for (int j = current_index; j < ADDRESS_SIZE; ++j)
            if (structure->future_usage[j] == structure->pages[i]) {
                dist = j;
            }

        if (dist == -1)
            return i;
        if (dist > farthest)
        {
            farthest = dist;
            index = i;
        }
    }

    return index;
}

int optimal_add_page(Optimal *structure, int page, int current_index)
{
    if (!structure)
    {
        fprintf(stderr, "Error: OPT not initialized.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->size; i++)
        if (structure->pages[i] == page)
        {
            return i;
        }

    if (structure->size == structure->capacity)
    {
        int index = optimal_choose_page_to_replace(structure, current_index);

        structure->pages[index] = page;
        return index;
    }

    structure->pages[structure->size++] = page;
    return -1;
}

void free_optimal(Optimal *structure)
{
    if (structure->pages)
    {
        free(structure->pages);
        structure->pages = NULL;
    }
    if (structure->future_usage)
    {
        free(structure->future_usage);
        structure->future_usage = NULL;
    }
    structure->capacity = structure->size = 0;
}

void print_optimal(const Optimal *structure)
{
    printf("Optimal Structure:\n");
    for (int i = 0; i < structure->size; i++)
        printf("%d ", structure->pages[i]);
    printf("\n");
}
