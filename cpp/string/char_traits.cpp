#include <iostream>
#include <string>

int main()
{
    char ch[8] = {0};

    std::string sss = "";

    //std::char_traits<char>::copy(ch, sss.c_str()+3, 8);
    //std::cout << ch << std::endl;
    std::cout << ch[10] << std::endl;

    std::string s2(sss.c_str() + 5, 8);

    std::string * s3 = nullptr;
    std::string s4(s3->c_str() + 5, 8);
}
