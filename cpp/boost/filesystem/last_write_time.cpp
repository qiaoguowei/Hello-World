#include <iostream>
#include <boost/filesystem.hpp>
#include <time.h>

int main()
{
    boost::filesystem::path p("/home/qgw/my_github/Hello-World/cpp/boost/filesystem");
    boost::filesystem::directory_iterator end_iter;
    for (boost::filesystem::directory_iterator file_iter(p); file_iter != end_iter; ++file_iter)
    {
        boost::system::error_code ec;
        time_t rawtm = boost::filesystem::last_write_time(file_iter->path(), ec);
        struct tm *timeinfo = localtime(&rawtm);
        char buffer[255] = {0};
        strftime(buffer, 255, "%Y-%m-%d %H:%M:%S", timeinfo); 
        std::cout << "last write time is " << buffer << ", file name is " << file_iter->path().string() << std::endl;
    }
}
