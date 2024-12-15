#include "../../lib/utils/utils.h"

void parser_input_file_int(const char *filename, int* lines, int capacity)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    int temp;
    for (int i = 0; i < capacity; i++)
    {
        fscanf(file, "%d", &temp);
        lines[i] = temp;
    }

    fclose(file);
}

void parser_input_file_data(const char *filename, char *data, int capacity)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    fread(data, sizeof(char), capacity, file);
    fclose(file);
}