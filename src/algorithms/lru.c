#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lru.h"

typedef struct {
    int page;
    int timestamp;
} LRUEntry;

static LRUEntry *table = NULL;
static int capacity = 0;
static int time = 0;

void initialize_lru(int capacity_value) {
    if (capacity_value <= 0) {
        fprintf(stderr, "LRU Error: Invalid capacity value!\n");
        exit(EXIT_FAILURE);
    }

    if (table != NULL) {
        fprintf(stderr, "LRU Warning: Table is already initialized.\n");
        return;
    }

    capacity = capacity_value;
    table = (LRUEntry *)malloc(capacity * sizeof(LRUEntry));
    if (!table) {
        perror("LRU Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < capacity; i++) {
        table[i].page = -1;      
        table[i].timestamp = -1; 
    }
    time = 0;
}

int lru_choose_page_to_replace() {
    int oldest_time = INT_MAX;
    int oldest_index = -1;

    for (int i = 0; i < capacity; i++) {
        if (table[i].timestamp < oldest_time) {
            oldest_time = table[i].timestamp;
            oldest_index = i;
        }
    }

    return oldest_index; 
}

void lru_access_page(int page) {
    time++;

    for (int i = 0; i < capacity; i++) {
        if (table[i].page == page) {
            table[i].timestamp = time; 
            return;
        }
    }

    for (int i = 0; i < capacity; i++) {
        if (table[i].page == -1) {
            table[i].page = page;
            table[i].timestamp = time;
            return;
        }
    }

    int replace_index = lru_choose_page_to_replace();
    table[replace_index].page = page;
    table[replace_index].timestamp = time;
}

void free_lru() {
    if (table) {
        free(table);
        table = NULL;
    }
    capacity = 0;
    time = 0;
}
