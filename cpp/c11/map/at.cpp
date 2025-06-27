#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> aa;
    aa.insert(std::make_pair<std::string, int>("aaa", 1));

    std::cout << "aa.size() is [" << aa.size() << "]" << std::endl;

    if (aa["bbb"] == 2)
    {
        std::cout << "version is equal." << std::endl;
    }
    else
    {
        std::cout << "version is not equal." << std::endl;
    }

    std::cout << aa["bbb"] << std::endl;
    std::cout << "aa.size() is [" << aa.size() << "]" << std::endl;

    return 0;
}
