#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

static int *queue = NULL;
static int capacity = 0;
static int front = 0, rear = 0, size = 0;

void initialize_fifo(int capacity_value) {
    if (capacity_value <= 0) {
        fprintf(stderr, "FIFO Error: Invalid capacity value!\n");
        exit(EXIT_FAILURE);
    }

    if (queue != NULL) {
        fprintf(stderr, "FIFO Warning: Queue is already initialized.\n");
        return;
    }

    capacity = capacity_value;
    queue = (int *)malloc(capacity * sizeof(int));
    if (!queue) {
        perror("FIFO Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    front = rear = size = 0;
}

int fifo_choose_page_to_replace() {
    if (size == 0) {
        fprintf(stderr, "FIFO Error: No pages to replace (queue is empty)!\n");
        return -1; 
    }

    int page = queue[front];
    front = (front + 1) % capacity; 
    size--;
    return page;
}

void fifo_add_page(int page) {
    if (size == capacity) {
        int replaced_page = fifo_choose_page_to_replace();
        if (replaced_page == -1) {
            return; 
        }
    }

    queue[rear] = page;
    rear = (rear + 1) % capacity; 
    size++;
}

void free_fifo() {
    if (queue) {
        free(queue);
        queue = NULL;
    }
    capacity = front = rear = size = 0;
}
