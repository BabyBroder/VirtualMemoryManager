#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int offset = 200;
int main()
{
    srand(time(NULL));
    freopen("../data/addresses.txt","w",stdout);
    for(int i = 0 ;i<=1000; i++) 
        {
            int num = rand()%65536; 
        // tạo logical addresss bao gồm virtual address + offsets  
            printf("%d\n",num);
        }
    return 0;
}