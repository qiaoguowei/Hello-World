#include <iostream>
#include <map>

int main()
{
    std::multimap<int, std::string&> mm;

    std::string s1 = "aaa";
    std::string s2 = "bbb";
    std::string s3 = "ccc";

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;

    mm.insert(std::pair<int, std::string&>(1, s1));
    mm.insert(std::pair<int, std::string&>(2, s2));
    mm.insert(std::pair<int, std::string&>(3, s3));

    for (auto& xx : mm)
    {
        xx.second = "123456";
    }

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
}
