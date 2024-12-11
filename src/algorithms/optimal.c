#include "optimal.h"

void initialize_optimal(Optimal *structure, int capacity) {
    if (capacity <= 0) {
        fprintf(stderr, "Optimal Error: Invalid capacity value!\n");
        exit(EXIT_FAILURE);
    }
    
    structure->pages = NULL;
    structure->future_usage = NULL;
    structure->map = NULL;
    structure->idx = NULL;
    structure->capacity = capacity;
    structure->size = 0;
    structure->pages = (int *)malloc(structure->capacity * sizeof(int));
    if (!structure->pages) {
        perror("Optimal Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    structure->future_usage = (int *)malloc(1000 * sizeof(int));
    if (!structure->future_usage) {
        perror("Optimal Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    structure->map = (int *)malloc(65536 * sizeof(int));
    if (!structure->map) {
        perror("Optimal Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    structure->idx = (int **)malloc(1000 * sizeof(int *));
    if (!structure->idx) {
        perror("Optimal Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < structure->capacity; i++)
        structure->pages[i] = -1;
    for (int i = 0; i < 1000; i++)
        structure->future_usage[i] = 0;
    for (int i = 0; i < 65536; i++)
        structure->map[i] = -1;

    for (int i = 0; i < 1000; i++) {
        structure->idx[i] = (int *)malloc(1000 * sizeof(int));
        if (!structure->idx[i]) {
            perror("Optimal Error: Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < 1000; j++)
            structure->idx[i][j] = -1;
    }

    build_future_usage(structure);
}

void build_future_usage(Optimal *structure) {
    freopen("../../data/addresses.txt", "r", stdin);
    
    for (int page, i = 0; i < 1000; i++) {
        scanf("%d", &page);
        structure->future_usage[i] = page;
    }

    int _size = 0;

    for (int i = 999; i >= 0; i--) {
        if (i < 999) {
            for (int j = 0; j < _size; ++j)
                structure->idx[j][i] = structure->idx[j][i + 1];
        }

        if (structure->map[structure->future_usage[i]] == -1) 
            structure->map[structure->future_usage[i]] = _size++;

        structure->idx[structure->map[structure->future_usage[i]]][i] = i;
    }
}

int optimal_choose_page_to_replace(const Optimal *structure, int current_index) {
    if (structure->size == 0) {
        fprintf(stderr, "Optimal Error: No pages to replace (memory is empty)!\n");
        return -1;
    }

    return 0;
    int index = -1, farthest = -1;
    for (int i = 0; i < structure->capacity; i++) {
       if (structure->idx[structure->map[structure->pages[i]]][current_index] == -1)
            return i;
        if (structure->idx[structure->map[structure->pages[i]]][current_index] > farthest) {
            farthest = structure->idx[structure->map[structure->pages[i]]][current_index];
            index = i;
        }
    }

    return index;
}

bool optimal_add_page(Optimal *structure, int page, int current_index) {
    for (int i = 0; i < structure->size; i++)
        if (structure->pages[i] == page) 
            return true;

    if (structure->size < structure->capacity) {
        structure->pages[structure->size++] = page;
    } else {
        return false;

        // int index = optimal_choose_page_to_replace(structure, current_index);
        // structure->pages[index] = page;
    }

    return true;
}
void free_optimal(Optimal *structure) {
    if (structure->pages) {
        free(structure->pages);
        structure->pages = NULL;
    }
    if (structure->future_usage) {
        free(structure->future_usage);
        structure->future_usage = NULL;
    }
    if (structure->map) {
        free(structure->map);
        structure->map = NULL;
    }
    if (structure->idx) {
        for (int i = 0; i < 1000; i++) {
            if (structure->idx[i]) {
                free(structure->idx[i]);
                structure->idx[i] = NULL;
            }
        }
        free(structure->idx);
        structure->idx = NULL;
    }
    structure->capacity = structure->size = 0;
}