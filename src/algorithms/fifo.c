#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

void initialize_fifo(FIFO *structure, int capacity_value) {
    if (capacity_value <= 0) {
        fprintf(stderr, "FIFO Error: Invalid capacity value!\n");
        exit(EXIT_FAILURE);
    }

    if (structure->queue != NULL) {
        fprintf(stderr, "FIFO Warning: Queue is already initialized.\n");
        return;
    }

    structure->capacity = capacity_value;
    structure->queue = (int *)malloc(structure->capacity * sizeof(int));
    if (!structure->queue) {
        perror("FIFO Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    structure->front = structure->rear = structure->size = 0;
}

int fifo_choose_page_to_replace(FIFO *structure) {
    if (structure->size == 0) {
        fprintf(stderr, "FIFO Error: No pages to replace (queue is empty)!\n");
        return -1; 
    }

    int page = structure->queue[structure->front];
    structure->front = (structure->front + 1) % structure->capacity; 
    structure->size--;
    return page;
}

void fifo_add_page(FIFO *structure, int page) {
    if (structure->size == structure->capacity) {
        for (int i = 0; i < structure->size; i++) {
            if (structure->queue[i] == page) {
                return; 
            }
        }
        fifo_choose_page_to_replace(structure);
    }

    structure->queue[structure->rear] = page;
    structure->rear = (structure->rear + 1) % structure->capacity; 
    structure->size++;
}

void free_fifo(FIFO *structure) {
    if (structure->queue) {
        free(structure->queue);
        structure->queue = NULL;
    }
    structure->capacity = structure->front = structure->rear = structure->size = 0;
}
