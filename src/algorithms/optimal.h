#ifndef OPTIMAL_H
#define OPTIMAL_H

#include <stddef.h> // For size_t
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "../virtual_memory.h"

typedef struct
{
    int *pages;        // Array to store the pages currently in memory
    int capacity;      // Maximum number of pages the memory can hold
    int size;          // Current number of pages in memory
    int *future_usage; // Array to track future usage of pages
    int *map;
    int **idx;
} Optimal;

/**
 * Initializes the Optimal structure with the specified capacity.
 *
 * @param structure Pointer to the Optimal structure to initialize.
 * @param capacity The maximum number of pages the memory can hold.
 */
void initialize_optimal(Optimal *structure, VirtualMemory *virtual_memory, int capacity);

/**
 * @brief Builds the future usage pattern for the optimal page replacement algorithm.
 *
 * This function analyzes the future memory access pattern and constructs the
 * necessary data structures to determine the optimal page to replace in the
 * future. It is used by the Optimal page replacement algorithm to minimize
 * page faults by always replacing the page that will not be used for the
 * longest period of time.
 *
 * @param structure A pointer to the Optimal structure that holds the data
 *                  necessary for the optimal page replacement algorithm.
 */
void build_future_usage(Optimal *structure);

/**
 * Chooses the page to replace using the Optimal page replacement algorithm.
 *
 * @param structure Pointer to the Optimal structure.
 * @param current_index The current index in the reference string.
 * @return The index of the page to replace in the Optimal structure.
 */
int optimal_choose_page_to_replace(const Optimal *structure, int current_index);

/**
 * Adds a page to the Optimal structure.
 *
 * @param structure Pointer to the Optimal structure.
 * @param page The page to add.
 */
bool optimal_add_page(Optimal *structure, int page, int current_index);

/**
 * Frees the dynamically allocated memory used by the Optimal structure.
 *
 * @param structure Pointer to the Optimal structure.
 */
void free_optimal(Optimal *structure);

/**
 * Prints the contents of the Optimal structure.
 *
 * @param structure Pointer to the Optimal structure.
 */
void print_optimal(const Optimal *structure);

#endif // OPTIMAL_H