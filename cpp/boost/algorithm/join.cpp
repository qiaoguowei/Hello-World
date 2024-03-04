#include <iostream>
#include <boost/algorithm/string/join.hpp>
#include <string>
#include <list>

int main()
{
    std::list<std::string> m_list;
    m_list.push_back(std::string("aaa"));
    m_list.push_back(std::string("bbb"));
    m_list.push_back(std::string("ccc"));
    m_list.push_back(std::string("ddd"));

    std::string ret = boost::join(m_list, ",");

    std::cout << ret << std::endl;
}
