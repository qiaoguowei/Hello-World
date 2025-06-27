#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/ratio.hpp>

int main()
{
    try
    {
        boost::filesystem::path m_path = boost::filesystem::initial_path();
        boost::filesystem::space_info m_space_info = boost::filesystem::space(m_path);
        std::cout << "磁盘空间：" << m_space_info.capacity / boost::giga::num << std::endl;
        std::cout << "磁盘可用空间：" << m_space_info.free / boost::giga::num << std::endl;
        std::cout << "磁盘可用空间：" << m_space_info.available / boost::giga::num << std::endl;
    }
    catch (boost::filesystem::filesystem_error& e)
    {
        std::cout << e.path1() << std::endl;
        std::cout << e.path2() << std::endl;
        std::cout << e.what() << std::endl;
    }
}
