#include <iostream>
#include <boost/filesystem.hpp>

namespace bf = boost::filesystem;

int main()
{
    bf::recursive_directory_iterator end;
    std::string m_path = "/home/qgw/program/cplusplus";
    for(bf::recursive_directory_iterator pos(m_path); pos != end; ++pos)
    {
        bf::path p = pos->path();
        std::string file_name = p.filename().string();
        std::string file_path = p.string();
        int depth = pos.depth();

        std::cout << "filename = " << file_name << ", file_path = " << file_path << ", depth = " << depth << std::endl;
    }
}
