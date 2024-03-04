#include <iostream>
#include <string>
#include <boost/filesystem/operations.hpp>

int main()
{
    //get local path, is equal to pwd
    boost::filesystem::path m_path = boost::filesystem::initial_path();
    std::cout << m_path.string() << std::endl;
}
