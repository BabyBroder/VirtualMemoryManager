#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_BYTE 256 * 30  // Define the number of bytes to write

int main() {
    // Open the file in binary write mode
    FILE *file = fopen("BACKINGSTORE.bin", "wb");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Seed the random number generator
    srand((unsigned)time(NULL));

    // Write random bytes to the file
    for (size_t i = 0; i < NUMBER_BYTE; i++) {
        unsigned char random_byte = rand() % 256; // Random byte (0 to 255)
        if (fwrite(&random_byte, sizeof(unsigned char), 1, file) != 1) {
            perror("Error writing to file");
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    printf("Successfully wrote %d random bytes to BACKINGSTORE.bin\n", NUMBER_BYTE);

    // Close the file
    fclose(file);
    return EXIT_SUCCESS;
}
