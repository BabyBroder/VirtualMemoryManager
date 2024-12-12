#include "lru.h"

void initialize_lru(LRU *structure, int capacity_value) {
    if (capacity_value <= 0) {
        fprintf(stderr, "LRU Error: Invalid capacity value!\n");
        exit(EXIT_FAILURE);
    }

    if (structure->table != NULL) {
        fprintf(stderr, "LRU Warning: Table is already initialized.\n");
        return;
    }

    structure->capacity = capacity_value;
    structure->size = structure->time = 0;
    structure->table = (LRUEntry *)malloc(structure->capacity * sizeof(LRUEntry));
    
    if (!structure->table) {
        perror("LRU Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->capacity; i++) {
        structure->table[i].page = -1;
        structure->table[i].timestamp = INT_MAX;
    }
}


int lru_choose_page_to_replace(LRU *structure) {
    if (structure->size == 0) {
        fprintf(stderr, "LRU Error: No pages to replace (table is empty)!\n");
        return -1;
    }

    int min_timestamp = INT_MAX;
    int index = -1;
    for (int i = 0; i < structure->capacity; i++) {
        if (structure->table[i].timestamp < min_timestamp) {
            min_timestamp = structure->table[i].timestamp;
            index = i;
        }
    }
    //printf("LRU: Replacing index %d\n", index);
    return index;
}

bool lru_add_page(LRU *structure, int page) {
    ++structure->time;

    for (int i = 0; i < structure->size; i++) 
    {
        if (structure->table[i].page == page)
        {
            structure->table[i].timestamp = structure->time;
            //printf("LRU: Page %d already in memory\n", page);
            //print_lru(structure);
            return true;
        }
    }

    if (structure->size == structure->capacity) {
        int index = lru_choose_page_to_replace(structure);
        structure->table[index].page = page;
        structure->table[index].timestamp = structure->time;
        //printf("LRU: Replacing index %d with page %d\n", index, page);
        //print_lru(structure);
        return false; 
    }

    structure->table[structure->size].page = page;
    structure->table[structure->size].timestamp = structure->time;
    ++structure->size;
    //printf("LRU: Adding page %d\n", page);
    //print_lru(structure);
    return true;
}

void free_lru(LRU *structure) {
    if (structure->table) {
        free(structure->table);
        structure->table = NULL;
    }
    structure->capacity = structure->size = structure->time = 0;
}

void print_lru(LRU *structure) {
    printf("LRU Table: ");
    for (int i = 0; i < structure->size; i++) {
        printf("%d ", structure->table[i].page);
    }
    printf("\n");
}