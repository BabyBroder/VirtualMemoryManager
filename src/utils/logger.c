#include "utils/utils.h"

void log_event(const char *fileLog, const char *message)
{
    FILE *file = fopen(fileLog, "a");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", fileLog);
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", message);
    fclose(file);
}