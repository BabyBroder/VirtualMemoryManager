#include "utils/utils.h"

void parser_input_file_int(char *filename, int *lines, int capacity)
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

void parser_input_file_data(char *filename, char *data, int capacity)
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

void write_to_output_file(char *filename, char *data)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    fprintf(file, "%s\n", data);
    fclose(file);
}