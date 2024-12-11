#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *queue;
    int capacity;
    int front, rear, size;
} FIFO;

void initialize_fifo(FIFO* structure, int capacity);
int fifo_choose_page_to_replace(FIFO* structure);
bool fifo_add_page(FIFO* structure, int page);
void free_fifo(FIFO* structure);

#endif // FIFO_H
