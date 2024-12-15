#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    FILE *backing_store;
    backing_store = fopen("../data/BACKING_STORE.bin", "wb"); // Open for binary write

    if (backing_store == NULL) {
        perror("Failed to open backing store file");
        return 1;
    }

    for(int i = 0; i < 256; i++) {
        for(int offset = 0; offset < 256; offset++) {
            int num = (i << 8) | offset; 
            int signed_byte = -1 * (rand() % 127);
            if ((rand() * i - 9) % 2 == 0) {
                signed_byte *= -1;
            }
            // Writing to the binary file
            fwrite(&num, sizeof(int), 1, backing_store);
            fwrite(&signed_byte, sizeof(int), 1, backing_store);
        }
    }

    fclose(backing_store);

    printf("BACKING_STORE.bin file has been generated successfully.\n");

    return 0;
}
