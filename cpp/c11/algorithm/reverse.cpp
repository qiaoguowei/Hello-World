#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void test1()
{
    std::string str = "abcdefghijklmnopqrstucwxyz123456";
    std::cout << str << std::endl;
    std::reverse(str.begin(), str.begin()+8);
    std::cout << str << std::endl;
    std::reverse(str.begin()+8, str.begin()+16);
    std::cout << str << std::endl;
    std::reverse(str.begin()+16, str.begin()+24);
    std::cout << str << std::endl;
    std::reverse(str.begin(), str.end());
    std::cout << str << std::endl;
}

int main()
{
#if 0
    string str1 = "abcdefg";
    std::reverse(str1.begin(), str1.end());//将区间内的元素反转放置

    cout << str1 << endl;
#endif
    test1();
}
