#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    std::ifstream fin("/home/qgw/include/skyguard/base/CombinedBlockInfo.h", std::ios::binary);
    if (!fin)
    {
        std::cout << "open file failed." << strerror(errno) << std::endl;
        return -1;
    }

    std::stringstream ss;
    ss << fin.rdbuf();
    fin.close();

    std::string write_str = ss.str();
    std::cout << write_str.size() << std::endl;

    FILE *file = fopen("./xxx.txt", "wb");

    size_t write_size = fwrite(write_str.c_str(), write_str.size(), 1, file);
    fclose(file);

    struct stat file_info;
    memset(&file_info, 0, sizeof(struct stat));
    if (0 != stat("./xxx.txt", &file_info))
    {
        return false;
    }
    uint64_t file_size = file_info.st_blocks * 512;
    std::cout << file_size << std::endl;
}
