#include <iostream>
#include <strings.h>

int main()
{
    std::string s1 = "aaaaabbb";
    std::string s2 = "AAAAAccc";

    int ret = strcasecmp(s1.c_str(), s2.c_str());
    std::cout << "ret = " << ret << std::endl;

    int ret2 = strncasecmp(s1.c_str(), s2.c_str(), 5);
    std::cout << "ret = " << ret2 << std::endl;
}
