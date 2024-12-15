#include "../../lib/algorithms/algorithms.h"

void initialize_optimal(Optimal *structure, VirtualMemory *virtual_memory, int capacity)
{

    if (structure->capacity > 0)
    {
        printf("capacity: %d\n", capacity);
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
    structure->future_usage = (int *)malloc(1000 * sizeof(int));
    structure->map = (int *)malloc(65536 * sizeof(int));
    structure->idx = (int **)malloc(1000 * sizeof(int *));

    if (!structure->pages || !structure->future_usage || !structure->map || !structure->idx)
    {
        perror("Optimal Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->capacity; i++)
        structure->pages[i] = -1;

    // Write address to future_usage
    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        structure->future_usage[i] = virtual_memory->address[i];
    }

    // check later
    for (int i = 0; i < 1000; i++)
        structure->future_usage[i] = structure->future_usage[i] & 0xFFFF;

    for (int i = 0; i < 65536; i++)
        structure->map[i] = -1;

    for (int i = 0; i < 1000; i++)
    {
        structure->idx[i] = (int *)malloc(1000 * sizeof(int));
        if (!structure->idx[i])
        {
            perror("Optimal Error: Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < 1000; j++)
            structure->idx[i][j] = -1;
    }

    build_future_usage(structure);
}

void build_future_usage(Optimal *structure)
{
    int _size = 0;

    for (int i = 999; i >= 0; i--)
    {
        if (i < 999)
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

int optimal_choose_page_to_replace(const Optimal *structure, int current_index)
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
        if (structure->idx[structure->map[structure->pages[i]]][current_index] == -1)
            return i;
        if (structure->idx[structure->map[structure->pages[i]]][current_index] > farthest)
        {
            farthest = structure->idx[structure->map[structure->pages[i]]][current_index];
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
            return -2;
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
    if (structure->map)
    {
        free(structure->map);
        structure->map = NULL;
    }
    if (structure->idx)
    {
        for (int i = 0; i < 1000; i++)
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
        printf("%d ", structure->pages[i]);
    printf("\n");
}