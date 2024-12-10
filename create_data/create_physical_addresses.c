#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    freopen("../data/physical_addresses.txt", "w", stdout);

    for(int i=0 ; i<256; i++) 
        {
            for(int offset = 0 ; offset<256; offset++)
            {
                int num = (i<<8)|offset; 
                int signed_byte = -1*rand()%127;
                if((rand()*i-9)%2==0){
                signed_byte*=-1;
                printf("%d %d\n",num,signed_byte);
            }
        }
    }
    return 0;
}
