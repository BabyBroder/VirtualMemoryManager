#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>

// Function to parse the input file int
void parser_input_file_int(const char *filename, int line[], int capacity);
// Function to parse the input file data
void parser_input_file_data(const char *filename, char* data, int capacity);

#endif // PARSER_H