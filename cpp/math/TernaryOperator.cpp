#include <iostream>

int main()
{
    int startOffset = 100;
    int size = 1024;

    int length = size - startOffset > 512 ? startOffset + 512 : size;
    std::cout << length << std::endl;
}
