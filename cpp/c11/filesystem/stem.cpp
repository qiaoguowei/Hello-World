#include <iostream>
#include <filesystem>


int main()
{
    std::filesystem::path path("/home/qgw/my_github/Hello-World/cpp/c11/filesystem/log/test.log");
    std::string baseName = path.stem().string();
    std::cout << baseName << std::endl;
}
