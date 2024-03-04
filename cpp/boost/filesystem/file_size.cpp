#include <iostream>
//#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
namespace bf = boost::filesystem;

int main()
{
    try
    {
        std::string mpath = "/home/qgw/my_github/Hello-World/cpp/boost/filesystem";
        cout << bf::file_size(mpath) << endl;
    }
    catch (boost::filesystem::filesystem_error& e)
    {
        std::cout << e.what() << std::endl;
    }
}
