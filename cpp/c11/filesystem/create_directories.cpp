#include <iostream>
#include <filesystem>

int main()
{
    std::string filePath_ = "/home/qgw/my_github/Hello-World/cpp/c11/filesystem/log";
    std::filesystem::path path(filePath_);
    std::cout << path.parent_path().string() << std::endl;
    std::filesystem::create_directories(path);
}
