#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int num_line = 10;
const int range = 65536;
const char* file_test = "../test/addresses.txt";
int main()
{
    srand(time(NULL));
    freopen(file_test, "w", stdout);
    for(int i = 0; i < num_line; i++) {
        int offset = rand() % 256;
        int num = (i << 8) | offset;
        printf("%d\n", num);
    }
    return 0;
}