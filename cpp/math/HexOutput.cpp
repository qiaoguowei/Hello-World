#include <iostream>
#include <boost/format.hpp>
#include <cstdlib>
#include <cstring>
#include <string>

int main()
{
    char *file_info = nullptr;
    file_info = (char *)malloc(128);
    if (file_info == nullptr)
    {
        std::cout << "malloc failed." << std::endl;
        return -1;
    }

    const char *xx = "abcdefg";
    strncpy(file_info, xx, strlen(xx));

    std::string hex_buf = "dump virus file name hex:\n";
    for (int i = 0; *(file_info + i); ++i)
    {
        hex_buf += (boost::format("0x%02x(%c) ") % (*(file_info + i) & 0xff) % *(file_info + i)).str();
    }
    std::cout << hex_buf << std::endl;

    free(file_info);
}
