#ifndef FIFO_H
#define FIFO_H

#include "../necessary.h"

/**
 * @brief Structure representing a FIFO (First-In-First-Out) queue.
 *
 * @var FIFO::queue Pointer to the array representing the queue.
 * @var FIFO::capacity Maximum number of elements the queue can hold.
 * @var FIFO::front Index of the front element in the queue.
 * @var FIFO::rear Index of the rear element in the queue.
 * @var FIFO::size Current number of elements in the queue.
 */
typedef struct
{
    int *queue;
    int capacity;
    int front, rear, size;
} FIFO;

/**
 * @brief Initializes the FIFO structure with a given capacity.
 *
 * @var FIFO::structure Pointer to the FIFO structure to initialize.
 * @var FIFO::capacity The maximum number of pages the FIFO structure can hold.
 */
void initialize_fifo(FIFO *structure, int capacity);

/**
 * @brief Chooses a page to replace based on the FIFO algorithm.
 *
 * @param structure Pointer to the FIFO structure.
 * @return The page number that should be replaced.
 */
int fifo_choose_page_to_replace(FIFO *structure);

/**
 * @brief Adds a page to the FIFO structure.
 *
 * @param structure Pointer to the FIFO structure.
 * @param page The page number to add.
 * @return 0 if the page was added successfully, or already exists in the FIFO structure; -1 if the FIFO structure is full.
 */
int fifo_add_page(FIFO *structure, int page);

/**
 * @brief Frees the resources allocated for the FIFO structure.
 *
 * @param structure Pointer to the FIFO structure to free.
 */
void free_fifo(FIFO *structure);

/**
 * @brief Prints the current state of the FIFO structure.
 *
 * @param structure Pointer to the FIFO structure to print.
 */
void print_fifo(FIFO *structure);

#endif // FIFO_H