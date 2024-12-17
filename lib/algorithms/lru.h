/**
 * @file lru.h
 * @brief Header file for the Least Recently Used (LRU) page replacement algorithm.
 */
#ifndef LRU_H
#define LRU_H

#include "../necessary.h"

/**
 * @brief Structure representing an entry in the LRU (Least Recently Used) table.
 *
 * This structure is used to keep track of pages in memory and their last access times.
 * It helps in implementing the LRU page replacement algorithm by storing the page number
 * and the timestamp of the last access.
 *
 * @var LRUEntry::page
 * The page number.
 * @var LRUEntry::timestamp
 * The timestamp indicating the last access time.
 */
typedef struct
{
	int page;				 /**< The page number. */
	unsigned long timestamp; /**< The timestamp indicating the last access time. */
} LRUEntry;

/**
 * @brief Structure representing the LRU (Least Recently Used) cache.
 *
 * This structure is used to manage a cache using the Least Recently Used (LRU) algorithm.
 * It keeps track of the entries in the cache, the maximum capacity of the cache, the current
 * number of entries, and a timestamp to manage the order of usage.
 *
 * @var LRU::table
 * Pointer to the array of LRU entries.
 *
 * @var LRU::capacity
 * Maximum number of entries the LRU cache can hold.
 *
 * @var LRU::size
 * Current number of entries in the LRU cache.
 *
 * @var LRU::time
 * Current time used for timestamping entries.
 */
typedef struct
{
	LRUEntry *table;	/**< Pointer to the array of LRU entries. */
	int capacity;		/**< Maximum number of entries the LRU cache can hold. */
	int size;			/**< Current number of entries in the LRU cache. */
	unsigned long time; /**< Current time used for timestamping entries. */
} LRU;

/**
 * @brief Initializes the LRU structure with the given capacity.
 *
 * @param structure Pointer to the LRU structure to initialize.
 * @param capacity The maximum number of entries the LRU cache can hold.
 */
void initialize_lru(LRU *structure, int capacity);

/**
 * @brief Chooses a page to replace based on the LRU policy.
 *
 * @param structure Pointer to the LRU structure.
 * @return The page number to replace.
 */
int lru_choose_page_to_replace(LRU *structure);

/**
 * @brief Adds a page to the LRU cache.
 *
 * @param structure Pointer to the LRU structure.
 * @param page The page number to add.
 * @return Index of the page in the queue if the page was replaced successfully or already exists, -1 if the queue is not full
 */
int lru_add_page(LRU *structure, int page);

/**
 * @brief Frees the memory allocated for the LRU structure.
 *
 * @param structure Pointer to the LRU structure to free.
 */
void free_lru(LRU *structure);

/**
 * @brief Prints the current state of the LRU cache.
 *
 * @param structure Pointer to the LRU structure to print.
 */
void print_lru(LRU *structure);

#endif // LRU_H