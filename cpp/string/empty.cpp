#include <iostream>
#include <string>


int main()
{
    std::string m_str;
    if (m_str.empty())
    {
        std::cout << "11111: the str is empty." << std::endl;
    }

    m_str = "aaaaaa";
    std::cout << m_str << std::endl;

    m_str = "";
    if (m_str.empty())
    {
        std::cout << "22222: the str is empty." << std::endl;
    }
}
