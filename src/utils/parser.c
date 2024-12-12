#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

void parse_input_file(const char *filename, int lines[], int capacity)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    int temp;
    for (int i = 0; i < capacity; i++) {
        fscanf(file, "%d", &temp);
        lines[i] = temp;
    }

    fclose(file);
}
