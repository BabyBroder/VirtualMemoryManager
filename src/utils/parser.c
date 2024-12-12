#include "../../lib/utils/utils.h"

/**
 * @brief Reads integers from a file and stores them in an array.
 *
 * This function opens a file in read mode, reads integers from the file,
 * and stores them in the provided array. If the file cannot be opened,
 * an error message is printed.
 *
 * @param filename The name of the file to read from.
 * @param lines An array to store the integers read from the file.
 * @param capacity The maximum number of integers to read.
 */
void parser_input_file_int(const char *filename, int lines[], int capacity)
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

/**
 * @brief Reads binary data from a file and stores it in a buffer.
 *
 * This function opens a file in binary read mode, reads data from the file,
 * and stores it in the provided buffer. If the file cannot be opened,
 * an error message is printed.
 *
 * @param filename The name of the file to read from.
 * @param data A buffer to store the data read from the file.
 * @param capacity The maximum number of bytes to read.
 */
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