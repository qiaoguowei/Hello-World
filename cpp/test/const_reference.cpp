#include <iostream>
#include <string>

void test1(const std::string& str1)
{
    std::cout << str1 << std::endl;
}

void test2(std::string& str2)
{
    std::cout << str2 << std::endl;
}

void test3(std::string&& str3)
{
    std::cout << str3 << std::endl;
}

int main()
{
    test1(std::string("test1"));
    std::string str2 = "test2";
    test2(str2);
    test3(std::string("test3"));
}



