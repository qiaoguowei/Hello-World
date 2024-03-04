#include <iostream>
#include <string>
#include <boost/format.hpp>

void test1()
{
    std::cout << boost::format("\nUsage:\n%6tDSAUtil set <file_name>\n") << std::endl;
}

void test2()
{
    int m_dsaid = 1;
    boost::format topic = boost::format("AGGS.%1%.internal.v1") %m_dsaid;
    std::cout << topic.str() << std::endl;
}

int main()
{
    test2();
}
