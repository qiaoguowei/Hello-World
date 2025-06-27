#include <iostream>

int main()
{
    uint32_t aa = 10485760000;

    std::cout << aa << std::endl;

    uint32_t cc = 10000;

    uint64_t bb = 10000ull * 1024 * 1024;

    std::cout << bb << std::endl;
}
