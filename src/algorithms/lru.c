#include "../../lib/algorithms/algorithms.h"

void initialize_lru(LRU *structure, int capacity_value)
{

    if (structure->capacity > 0)
    {
        fprintf(stderr, "Error: LRU already initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (capacity_value <= 0)
    {
        fprintf(stderr, "LRU Error: Invalid capacity value!\n");
        exit(EXIT_FAILURE);
    }

    structure->capacity = capacity_value;
    structure->size = structure->time = 0;
    structure->table = (LRUEntry *)malloc(structure->capacity * sizeof(LRUEntry));

    if (!structure->table)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->capacity; i++)
    {
        structure->table[i].page = -1;
        structure->table[i].timestamp = INT_MAX;
    }
}

int lru_choose_page_to_replace(LRU *structure)
{

    if (!structure)
    {
        fprintf(stderr, "Error: LRU not initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (structure->size == 0)
    {
        fprintf(stderr, "LRU Error: No pages to replace (table is empty)!\n");
        exit(EXIT_FAILURE);
    }

    int min_timestamp = INT_MAX;
    int index = -1;
    for (int i = 0; i < structure->capacity; i++)
    {
        if (structure->table[i].timestamp < min_timestamp)
        {
            min_timestamp = structure->table[i].timestamp;
            index = i;
        }
    }

    return index;
}

int lru_add_page(LRU *structure, int page)
{

    if (!structure)
    {
        fprintf(stderr, "Error: LRU not initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (structure->size > structure->capacity)
    {
        fprintf(stderr, "LRU Error: Capacity exceeded\n");
        exit(EXIT_FAILURE);
    }

    ++structure->time;

    for (int i = 0; i < structure->size; i++)
        if (structure->table[i].page == page)
        {
            structure->table[i].timestamp = structure->time;
            return i;
        }

    if (structure->size == structure->capacity)
    {
        int index = lru_choose_page_to_replace(structure);
        structure->table[index].page = page;
        structure->table[index].timestamp = structure->time;
        return index;
    }

    structure->table[structure->size].page = page;
    structure->table[structure->size].timestamp = structure->time;
    ++structure->size;

    return -1;
}

void free_lru(LRU *structure)
{
    if (structure->table)
    {
        free(structure->table);
        structure->table = NULL;
    }
    structure->capacity = structure->size = structure->time = 0;
    free(structure);
}

void print_lru(LRU *structure)
{
    printf("LRU Table: ");
    for (int i = 0; i < structure->size; i++)
    {
        printf("%d ", structure->table[i].page);
    }
    printf("\n");
}