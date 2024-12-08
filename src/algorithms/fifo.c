#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

static int *queue = NULL;
static int capacity = 0;
static int front = 0, rear = 0, size = 0;

void initialize_fifo(int capacity_value) {}

int fifo_choose_page_to_replace() {}

void fifo_add_page(int page) {}
