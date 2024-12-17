#include "../../lib/algorithms/algorithms.h"

void initialize_fifo(FIFO *structure, int capacity_value)
{

    if (structure->capacity > 0)
    {
        fprintf(stderr, "Error: FIFO already initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (capacity_value <= 0)
    {
        fprintf(stderr, "FIFO Error: Invalid capacity value!\n");
        exit(EXIT_FAILURE);
    }

    structure->capacity = capacity_value;
    structure->queue = (int *)malloc(structure->capacity * sizeof(int));

    if (!structure->queue)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->capacity; i++)
    {
        structure->queue[i] = -1;
    }

    structure->front = structure->rear = structure->size = 0;
}

int fifo_choose_page_to_replace(FIFO *structure)
{

    if (!structure)
    {
        fprintf(stderr, "Error: FIFO not initialized.\n");
        exit(EXIT_FAILURE);
    }

    if (structure->size == 0)
    {
        fprintf(stderr, "FIFO Error: No pages to replace (queue is empty)!\n");
        exit(EXIT_FAILURE);
    }

    int page = structure->front;
    structure->front = (structure->front + 1) % structure->capacity;

    return page;
}

int fifo_add_page(FIFO *structure, int page)
{

    if (!structure)
    {
        fprintf(stderr, "Error: FIFO not initialized.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->size; i++)
        if (structure->queue[i] == page)
            return i;

    if (structure->size == structure->capacity)
    {
        int indexReplace = fifo_choose_page_to_replace(structure);
        structure->queue[structure->rear] = page;
        structure->rear = (structure->rear + 1) % structure->capacity;

        return indexReplace;
    }

    structure->queue[structure->rear] = page;
    structure->rear = (structure->rear + 1) % structure->capacity;
    structure->size++;

    return -1;
}

void free_fifo(FIFO *structure)
{
    if (structure->queue)
    {
        free(structure->queue);
        structure->queue = NULL;
    }
    structure->capacity = structure->front = structure->rear = structure->size = 0;
    free(structure);
}

void print_fifo(FIFO *structure)
{
    if (structure->size == 0)
    {
        printf("FIFO Queue is empty\n");
        return;
    }

    printf("FIFO Queue: ");
    for (int i = 0; i < structure->size; i++)
    {
        printf("%d ", structure->queue[i]);
    }
    printf("\n");
}