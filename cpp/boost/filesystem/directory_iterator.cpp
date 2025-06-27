#include <iostream>
#include <boost/filesystem.hpp>
#include <list>

using namespace std;
namespace bf = boost::filesystem;

void test1()
{
    try
    {
        //bf::path p("/home/qgw/program/cplusplus/boost/filesystem/sdf");
        bf::path p("/root");
        bf::directory_iterator di(p);
    }
    catch(bf::filesystem_error &e)
    {
        cerr << "1111 : " << e.what() << endl;
    }
}

void test2()
{
    std::list<std::string> m_list;
    try
    {
        bf::path p("/home/qgw/my_github/Hello-World/cpp/boost/filesystem/testDir");
        bf::directory_iterator end_iter;
        for(bf::directory_iterator file_iter(p); file_iter != end_iter; ++file_iter)
        {
            std::cout << file_iter->path().string() << std::endl;
            std::cout << file_iter->path().filename().string() << std::endl;
            m_list.push_back(file_iter->path().string());
            //std::cout << *file_iter << std::endl;
            //std::cout << bf::system_complete(*file_iter).string() << std::endl;
        } //返回路径在当前文件系统中的完整路径(绝对路径)
    }
    catch(bf::filesystem_error &e)
    {
        std::cerr << "222: " << e.what() << endl;
    }

    m_list.sort();
    for (std::string& x : m_list)
    {
        std::cout << x << std::endl;
    }
}

int main()
{
    test2();
}






