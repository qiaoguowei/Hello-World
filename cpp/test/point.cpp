#include <iostream>
#include <string.h>

int main()
{
    const unsigned char * data = (const unsigned char *)"abcdefghij111111112222222211111111";
    int len = strlen((const char *)data);

    while (len >= 8)
    {
        uint64_t one = *(uint64_t*)data;
        //uint64_t one = *(reinterpret_cast<uint64_t*>(const_cast<unsigned char*>(data)));

        std::cout << one << std::endl;

        std::cout << *(uint8_t*)data << std::endl;
        data += 8;
        len -= 8;
    }
}
