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

    // Choose the front page to replace
    int page = structure->front;
    structure->front = (structure->front + 1) % structure->capacity; 

    //printf("FIFO: Replacing index %d\n", page);
    return page;
}

bool fifo_add_page(FIFO *structure, int page) {
    for (int i = 0; i < structure->size; i++) 
    {
        if (structure->queue[i] == page)
        {
            //printf("FIFO: Page %d already in memory\n", page);
            //print_fifo(structure);
            return true;
        }
    }

    if (structure->size == structure->capacity) {

        int indexReplace = fifo_choose_page_to_replace(structure);
        if (indexReplace == -1) {
            fprintf(stderr, "FIFO Error: Failed to choose page to replace\n");
            exit(EXIT_FAILURE);
        }

        structure->queue[indexReplace] = page;
        //printf("FIFO: Replacing index %d with page %d\n", indexReplace, page);
        //print_fifo(structure);
        return false;
    }

    structure->queue[structure->rear] = page;
    structure->rear = (structure->rear + 1) % structure->capacity; 
    structure->size++;
    //printf("FIFO: Adding page %d\n", page);
    //print_fifo(structure);
    return true; 
}

void free_fifo(FIFO *structure) {
    if (structure->queue) {
        free(structure->queue);
        structure->queue = NULL;
    }
    structure->capacity = structure->front = structure->rear = structure->size = 0;
}

void print_fifo(FIFO *structure) {
    if (structure->size == 0) {
        printf("FIFO Queue is empty\n");
        return;
    }

    printf("FIFO Queue: ");
    for (int i = 0; i < structure->size; i++) {
        printf("%d ", structure->queue[i]);
    }
    printf("\n");
}