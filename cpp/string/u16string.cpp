#include <iostream>
#include <string>
#include <boost/locale.hpp>

int main()
{
    std::string str1 = "乔国伟abc";
    std::cout << str1.size() << std::endl;

    std::u16string str2 = boost::locale::conv::utf_to_utf<char16_t, char>(str1);;
    std::cout << str2.size() << std::endl;
}
