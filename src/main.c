#include"main.h"
int get_physical_address(uint8_t frame_number, uint8_t offset)
{
    return frame_number * FRAME_SIZE + offset;
}
int main()
{
    return 0;
}


