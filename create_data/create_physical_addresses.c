#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int offset = 200;
int main()
{
    srand(time(NULL));
    freopen("C:\\Users\\DELL\\VirtualMemoryManager\\VirtualMemoryManager\\data\\physical_addresses.txt","w",stdout);
    //  
    for(int i =0 ; i<256; i++) 
        {
            int num = (i<<8) | offset; 
            int signed_byte = -1*rand()%127;
            if((rand()*i-10)%2==0){
                signed_byte*=-1;
            }
            printf("%d %d\n",num,signed_byte);
        }
    return 0;
}