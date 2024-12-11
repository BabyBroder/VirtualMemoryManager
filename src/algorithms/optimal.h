#ifndef OPTIMAL_H
#define OPTIMAL_H

#include <stddef.h> // For size_t

typedef struct {
    int *pages;         // Array to store the pages currently in memory
    int capacity;       // Maximum number of pages the memory can hold
    int size;           // Current number of pages in memory
    int *future_usage;  // Array to track future usage of pages
    int *map;
    int **idx;    
} Optimal;

void build_future_usage(Optimal *structure);
/**
 * Initializes the Optimal structure with the specified capacity.
 * 
 * @param structure Pointer to the Optimal structure to initialize.
 * @param capacity The maximum number of pages the memory can hold.
 */
void initialize_optimal(Optimal *structure, int capacity);

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
void optimal_add_page(Optimal *structure, int page, int current_index);

/**
 * Frees the dynamically allocated memory used by the Optimal structure.
 * 
 * @param structure Pointer to the Optimal structure.
 */
void free_optimal_memory(Optimal *structure);

#endif // OPTIMAL_H