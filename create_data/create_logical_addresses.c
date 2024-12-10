#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    freopen("..\\data\\logical_addresses.txt","w",stdout);
    for(int i = 0 ;i<=65535; i++) 
        {
            int num = rand()%65535;
             printf("%d\n",num);
        }
    return 0;
}