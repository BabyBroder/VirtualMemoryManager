/**
 * @file lru.h
 * @brief Header file for the Least Recently Used (LRU) page replacement algorithm.
*/
#ifndef LRU_H
#define LRU_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


/**
 * @struct LRUEntry
 * @brief Represents an entry in the LRU table.
 * 
 * @var LRUEntry::page
 * The page number.
 * 
 * @var LRUEntry::timestamp
 * The timestamp indicating the last access time of the page.
 */
typedef struct {
	int page;
	unsigned long timestamp;
} LRUEntry;

/**
 * @struct LRU
 * @brief Represents the LRU structure.
 * 
 * @var LRU::table
 * Pointer to an array of LRUEntry representing the LRU table.
 * 
 * @var LRU::capacity
 * The maximum number of entries the LRU table can hold.
 * 
 * @var LRU::size
 * The current number of entries in the LRU table.
 * 
 * @var LRU::time
 * The current time, used for timestamping entries.
 */
typedef struct {
	LRUEntry *table;
	int capacity;
	int size;
	unsigned long time;
} LRU;

/**
 * @brief Initializes the LRU structure.
 * 
 * @param structure Pointer to the LRU structure to initialize.
 * @param capacity The maximum number of entries the LRU table can hold.
 */
void initialize_lru(LRU *structure, int capacity);

/**
 * @brief Chooses a page to replace based on the LRU algorithm.
 * 
 * @param structure Pointer to the LRU structure.
 * @return The page number of the page to replace.
 */
int lru_choose_page_to_replace(LRU *structure);

/**
 * @brief Adds a page to the LRU table.
 * 
 * @param structure Pointer to the LRU structure.
 * @param page The page number to add.
 * @return true if the page was added successfully, false otherwise.
 */
bool lru_add_page(LRU *structure, int page);

/**
 * @brief Frees the resources allocated for the LRU structure.
 * 
 * @param structure Pointer to the LRU structure to free.
 */
void free_lru(LRU *structure);

/**
 * @brief Prints the contents of the LRU structure.
 * 
 * @param structure Pointer to the LRU structure to print.
 */
void print_lru(LRU *structure);

#endif // LRU_H