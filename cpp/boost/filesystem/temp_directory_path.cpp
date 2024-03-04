#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <sstream>

#ifdef WIN32
const std::string SEPARATOR("\\");
#elif (defined __APPLE__ && __MACH__)
const std::string SEPARATOR("/");
#else
const std::string SEPARATOR("/");
#endif

bool getTmpPath(std::string &tmpPath)
{
    std::stringstream ss;
    ss << boost::filesystem::temp_directory_path().string();
    ss << SEPARATOR << boost::filesystem::unique_path().string();
    tmpPath = ss.str();

    return true;
}

int main(int argc, char *argv[])
{
    std::string tmpPath;

    getTmpPath(tmpPath);
    std::cout << tmpPath << std::endl;
    std::cout << boost::filesystem::temp_directory_path().string() << std::endl;
}
