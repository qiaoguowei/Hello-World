#include <iostream>
#include <boost/algorithm/string/join.hpp>
#include <string>
#include <list>
#include <vector>

int main()
{
    std::list<std::string> m_list;
    m_list.push_back(std::string("aaa"));
    m_list.push_back(std::string("bbb"));
    m_list.push_back(std::string("ccc"));
    m_list.push_back(std::string("ddd"));

    //std::string ret = boost::join(m_list, " ");
    std::string ret = boost::join(m_list, ",");
    std::cout << ret << std::endl;

    std::vector<std::string> m_vec;
    std::string ret2 = boost::join(m_vec, ",");

    std::cout << ret2 << std::endl;

    ret.replace(0, 3, ret2);
    std::cout << ret << std::endl;
}
