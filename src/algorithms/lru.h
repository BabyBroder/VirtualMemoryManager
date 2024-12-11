#ifndef LRU_H
#define LRU_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int page;
    int timestamp;
} LRUEntry;

typedef struct {
    LRUEntry *table;
    int capacity;
    int size;
    int time;
} LRU;

void initialize_lru(LRU *structure, int capacity);
int lru_choose_page_to_replace(LRU *structure);
bool lru_add_page(LRU *structure, int page);
void free_lru(LRU *structure);

#endif // LRU_H
