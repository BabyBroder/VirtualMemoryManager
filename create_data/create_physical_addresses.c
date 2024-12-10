#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    freopen("..\\data\\physical_addresses.txt","w",stdout);
    //  
    for(int i = 196608 ;i<=262144; i++) 
        {
            int signed_byte = -1*rand()%127;
            if((rand()*i-10)%2==0){
                signed_byte*=-1;
            }
            printf("%d %d\n",i,signed_byte);
        }
    return 0;
}