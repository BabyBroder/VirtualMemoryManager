#ifndef OPTIMAL_H
#define OPTIMAL_H

#include "../necessary.h"
// For init address to OPT (Optimal) in build_future_usage
#include "../memory/virtual_memory.h"

/**
 * @struct Optimal
 * @brief Structure to represent the state of the Optimal page replacement algorithm.
 *
 * This structure contains the necessary information to implement the Optimal page replacement algorithm.
 *
 * @var Optimal::pages
 * Array to store the pages currently in memory.
 *
 * @var Optimal::capacity
 * Maximum number of pages the memory can hold.
 *
 * @var Optimal::size
 * Current number of pages in memory.
 *
 * @var Optimal::future_usage
 * Array to track future usage of pages. This helps in determining which page to replace.
 *
 * @var Optimal::map
 * Additional array for mapping purposes (specific usage can be defined based on implementation).
 *
 * @var Optimal::idx
 * 2D array to store indices (specific usage can be defined based on implementation).
 */
typedef struct
{
    int *pages;        // Array to store the pages currently in memory
    int capacity;      // Maximum number of pages the memory can hold
    int size;          // Current number of pages in memory
    int *future_usage; // Array to track future usage of pages
    int *map;
    int **idx;
    int initialized; // Flag to check if the structure is initialized
} Optimal;

/**
 * @brief Initializes the Optimal structure.
 *
 * @param structure Pointer to the Optimal structure to initialize.
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param capacity The capacity of the Optimal structure.
 */
void initialize_optimal(Optimal *structure, VirtualMemory *virtual_memory, int capacity);

/**
 * @brief Builds the future usage table for the Optimal structure.
 *
 * @param structure Pointer to the Optimal structure.
 */
void build_future_usage(Optimal *structure);

/**
 * @brief Chooses the page to replace based on the Optimal algorithm.
 *
 * @param structure Pointer to the Optimal structure.
 * @param current_index The current index in the page reference string.
 * @return The index of the page to replace.
 */
int optimal_choose_page_to_replace(const Optimal *structure, int current_index);

/**
 * @brief Adds a page to the Optimal structure.
 *
 * @param structure Pointer to the Optimal structure.
 * @param page The page number to add.
 * @param current_index The current index in the page reference string.
 * @return Index of page in queue if the page was replaced successfully, -1 if the queue is not full, -2 if the queue have no changed.
 */
int optimal_add_page(Optimal *structure, int page, int current_index);

/**
 * @brief Frees the memory allocated for the Optimal structure.
 *
 * @param structure Pointer to the Optimal structure to free.
 */
void free_optimal(Optimal *structure);

/**
 * @brief Prints the contents of the Optimal structure.
 *
 * @param structure Pointer to the Optimal structure to print.
 */
void print_optimal(const Optimal *structure);
#endif // OPTIMAL_H