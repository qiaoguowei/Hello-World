#include <iostream>
#include <string>

int main()
{
    std::string ss = "қалайсың";
    //std::cout << std::hex << ss[0] << std::endl;
    std::cout << ss << std::endl;
    std::cout << ss.size() << std::endl;

    for (auto x : ss)
    {
        printf("%x", x);
        printf("\n");
    }

    std::cout << "============================================" << std::endl;
    std::string qq = "乔";
    for (auto x : qq)
    {
        printf("%x", x);
        printf("\n");
    }
}
