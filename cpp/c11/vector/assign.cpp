#include <iostream>
#include <vector>
#include <string>
#include <list>

int main()
{
    std::list<std::string> m_list;
    std::vector<std::string> m_vec;

    m_list.push_back(std::string("aaa"));
    m_list.push_back(std::string("bbb"));
    m_list.push_back(std::string("ccc"));
    m_list.push_back(std::string("ddd"));

    m_vec.assign(m_list.begin(), m_list.end());

    for (const std::string& xx : m_vec)
    {
        std::cout << xx << std::endl;
    }
}
