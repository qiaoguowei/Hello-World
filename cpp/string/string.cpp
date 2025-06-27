#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str1 = "abcd" "dddddd";
	cout << str1 << endl;

    std::string str2 = "乔";
    std::cout << str2.size() << std::endl;
    std::cout << str2 << std::endl;

    std::u16string str3(str2.begin(), str2.end());
    std::cout << str3.size() << std::endl;
    //std::basic_ostream<char16_t> out;
    //out << str3 << std::endl;

    std::wstring str4(str2.begin(), str2.end());
    std::cout << str4.size() << std::endl;
    std::wcout << str4 << std::endl;
}
