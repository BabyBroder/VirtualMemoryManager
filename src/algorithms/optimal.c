#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "optimal.h"

static int *memory = NULL;
static int memory_size = 0;
static int *access_sequence = NULL;
static int sequence_length = 0;

void initialize_optimal(int capacity, int *sequence, int sequence_len) {
    if (capacity <= 0 || sequence == NULL || sequence_len <= 0) {
        fprintf(stderr, "Invalid initialization parameters.\n");
        return;
    }

    memory_size = capacity;
    memory = (int *)malloc(memory_size * sizeof(int));
    if (!memory) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < memory_size; i++) {
        memory[i] = -1; 
    }

    access_sequence = sequence;
    sequence_length = sequence_len;
}

int optimal_choose_page_to_replace(int current_index) {
    int farthest = -1;
    int replace_index = -1;

    for (int i = 0; i < memory_size; i++) {
        int page = memory[i];
        int next_use = INT_MAX;

        for (int j = current_index + 1; j < sequence_length; j++) {
            if (access_sequence[j] == page) {
                next_use = j;
                break;
            }
        }
        if (next_use == INT_MAX) {
            return i; 
        }

        if (next_use > farthest) {
            farthest = next_use;
            replace_index = i;
        }
    }

    return replace_index;
}

void optimal_add_page(int page, int current_index) {
    for (int i = 0; i < memory_size; i++) {
        if (memory[i] == page) {
            return; 
        }
    }

    for (int i = 0; i < memory_size; i++) {
        if (memory[i] == -1) {
            memory[i] = page; 
            return;
        }
    }

    int replace_index = optimal_choose_page_to_replace(current_index);
    memory[replace_index] = page;
}

void free_optimal_memory() {
    if (memory) {
        free(memory);
        memory = NULL;
    }
    memory_size = 0;
    access_sequence = NULL;
    sequence_length = 0;
}
