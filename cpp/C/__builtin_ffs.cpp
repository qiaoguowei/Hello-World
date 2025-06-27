#include <iostream>

int main()
{
    unsigned int a = 0x02;
    std::cout << __builtin_ffs(a) << std::endl;

    unsigned int b = 0x03;
    std::cout << __builtin_ffs(b) << std::endl;

    unsigned int c = 0x04;
    std::cout << __builtin_ffs(c) << std::endl;

    c = 0x08;
    std::cout << __builtin_ffs(c) << std::endl;

    c = 0x10;
    std::cout << __builtin_ffs(c) << std::endl;

    c = 0x20;
    std::cout << __builtin_ffs(c) << std::endl;
}
