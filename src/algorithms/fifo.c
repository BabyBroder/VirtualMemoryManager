#include "../../lib/algorithms/algorithms.h"

/**
 * @brief Initializes a FIFO structure with a given capacity.
 *
 * @param structure Pointer to the FIFO structure to initialize.
 * @param capacity Maximum number of elements the queue can hold.
 */
void initialize_fifo(FIFO *structure, int capacity_value)
{

    if (structure)
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

/**
 * @brief Chooses a page to replace based on the FIFO algorithm.
 *
 * @param structure Pointer to the FIFO structure.
 * @return The page number to be replaced.
 */
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

/**
 * @brief Adds a page to the FIFO queue.
 *
 * @param structure Pointer to the FIFO structure.
 * @param page The page number to add to the queue.
 * @return Index of page in queue if the page was replaced successfully, -1 if the queue is not full, -2 if the queue have no changed.
 */
int fifo_add_page(FIFO *structure, int page)
{

    if (!structure)
    {
        fprintf(stderr, "Error: FIFO not initialized.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->size; i++)
        if (structure->queue[i] == page)
            return -2;

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

/**
 * @brief Frees the memory allocated for the FIFO structure.
 *
 * @param structure Pointer to the FIFO structure to free.
 */
void free_fifo(FIFO *structure)
{
    if (structure->queue)
    {
        free(structure->queue);
        structure->queue = NULL;
    }
    structure->capacity = structure->front = structure->rear = structure->size = 0;
}

/**
 * @brief Prints the current state of the FIFO queue.
 *
 * @param structure Pointer to the FIFO structure to print.
 */
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