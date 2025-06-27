#include <iostream>

int main()
{
    std::cout << sizeof(uint32_t) << std::endl;

    union
    {
        uint8_t buf[sizeof(uint32_t)];
        uint32_t size;
    }framing;

    std::cout << sizeof(framing.size) << std::endl;
}
