#include <iostream>
#include <string>
#include <map>
#include <algorithm>

class Test
{
public:
    Test(int num)
        : m_num(num)
    {}

    bool operator()(const std::pair<int, std::string>& rhs);
private:
    int m_num;
};

bool Test::operator()(const std::pair<int, std::string>& rhs)
{
    return m_num == rhs.first;
}

int main()
{
    Test t(2);
#if 0
    if (t(2))
        std::cout << "equel..." << std::endl;
    else
        std::cout << "not equel." << std::endl;
#endif

    std::map<int, std::string> mm;
    mm.insert(std::make_pair<int, std::string>(1, std::string("aaa")));
    mm.insert(std::make_pair<int, std::string>(2, std::string("bbb")));
    mm.insert(std::make_pair<int, std::string>(3, std::string("ccc")));
    mm.insert(std::make_pair<int, std::string>(4, std::string("ddd")));

    auto ret = std::find_if(mm.begin(), mm.end(), t);
    if (ret != mm.end())
    {
        std::cout << ret->first << ", " << ret->second << std::endl;
    }
}
