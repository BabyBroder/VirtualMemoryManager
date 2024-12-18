#include "algorithms/algorithms.h"

void initialize_optimal(Optimal *structure, VirtualMemory *virtual_memory, int capacity)
{

    if (structure->initialized == 0xdeafbeef)
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

    structure->page_number = (int *)malloc(structure->capacity * sizeof(int));
    structure->future_usage = (int *)malloc(ADDRESS_SIZE * sizeof(int));
    structure->map = (int *)malloc((MAX_PAGE_NUMBER + 1) * sizeof(int));
    structure->idx = (int **)malloc(ADDRESS_SIZE * sizeof(int *));
    structure->initialized = 0xdeafbeef;

    if (!structure->page_number || !structure->future_usage || !structure->map || !structure->idx)
    {
        perror("Optimal Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->capacity; i++)
        structure->page_number[i] = -1;

    // Write address to future_usage
    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        int page_number = virtual_memory->address[i] >> 8 & 0xFF;
        structure->future_usage[i] = page_number;
    }

    for (int i = 0; i < (MAX_PAGE_NUMBER + 1); i++)
        structure->map[i] = -1;

    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        structure->idx[i] = (int *)malloc(ADDRESS_SIZE * sizeof(int));
        if (!structure->idx[i])
        {
            perror("Optimal Error: Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < ADDRESS_SIZE; j++)
            structure->idx[i][j] = -1;
    }

    build_future_usage(structure);
}

void build_future_usage(Optimal *structure)
{
    int _size = 0;

    for (int i = ADDRESS_SIZE - 1; i >= 0; i--)
    {
        if (i < ADDRESS_SIZE - 1)
        {
            for (int j = 0; j < _size; ++j)
                structure->idx[j][i] = structure->idx[j][i + 1];
        }

        int optimal_page = structure->future_usage[i];
        int optimal_idx = structure->map[optimal_page];

        if (optimal_idx == -1)
            optimal_idx = structure->map[optimal_page] = _size++;

        structure->idx[optimal_idx][i] = i;
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
        int page = structure->page_number[i];
        int map = structure->map[page];

        if (structure->idx[map][current_index] == -1)
            return i;
        if (structure->idx[map][current_index] > farthest)
        {
            farthest = structure->idx[map][current_index];
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
        if (structure->page_number[i] == page)
        {
            return i;
        }

    if (structure->size == structure->capacity)
    {
        int index = optimal_choose_page_to_replace(structure, current_index);

        structure->page_number[index] = page;
        return index;
    }

    structure->page_number[structure->size++] = page;
    return -1;
}

void free_optimal(Optimal *structure)
{
    if (structure->page_number)
    {
        free(structure->page_number);
        structure->page_number = NULL;
    }
    if (structure->future_usage)
    {
        free(structure->future_usage);
        structure->future_usage = NULL;
    }
    if (structure->map)
    {
        free(structure->map);
        structure->map = NULL;
    }
    if (structure->idx)
    {
        for (int i = 0; i < ADDRESS_SIZE; i++)
        {
            if (structure->idx[i])
            {
                free(structure->idx[i]);
                structure->idx[i] = NULL;
            }
        }
        free(structure->idx);
        structure->idx = NULL;
    }
    structure->capacity = structure->size = 0;
}

void print_optimal(const Optimal *structure)
{
    printf("Optimal Structure:\n");
    for (int i = 0; i < structure->size; i++)
        printf("%d ", structure->page_number[i]);
    printf("\n");
}
