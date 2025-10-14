#include <iostream>

int main()
{
    uint64_t channel_mask = 0;

    channel_mask |= 1 << 4;
    if (channel_mask & 1 << 3)
        std::cout << "1 << 3 is true" << std::endl;
    if (channel_mask & 1 << 4)
        std::cout << "1 << 4 is true" << std::endl;
}
