#ifndef PARSER_H
#define PARSER_H

#include "../necessary.h"
/**
 * @brief Parses an input file and stores integer values into an array.
 *
 * This function reads integer values from a specified file and stores them
 * into the provided array up to the given capacity.
 *
 * @param filename The path to the input file containing integer values.
 * @param line An array to store the parsed integer values.
 * @param capacity The maximum number of integers to store in the array.
 */
void parser_input_file_int(char *filename, int line[], int capacity);

/**
 * @brief Parses the input file data and stores it in the provided buffer.
 *
 * This function reads the contents of the file specified by the filename
 * and stores it in the provided data buffer up to the specified capacity.
 *
 * @param filename The path to the input file to be parsed.
 * @param data A pointer to the buffer where the file data will be stored.
 * @param capacity The maximum number of bytes to read from the file.
 */
void parser_input_file_data(char *filename, char *data, int capacity);

/**
 * @brief Writes data to the specified output file.
 *
 * This function opens the file specified by `filename` in write mode and writes
 * the provided `data` to it. If the file does not exist, it will be created.
 * If the file already exists, its contents will be overwritten.
 *
 * @param filename The name of the file to write to.
 * @param data The data to be written to the file.
 */
void write_to_output_file(char *filename, char *data);

#endif // PARSER_H