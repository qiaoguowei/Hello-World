#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
	std::string str1 = "abcdefg";
	std::wstring wstr1(str1.begin(), str1.end());

	cout << str1 << endl;
	wcout << wstr1 << endl;
	cout << str1.size() << endl;
	cout << wstr1.size() << endl;
	cout << strlen(str1.c_str()) << endl;
	//cout << wstr1.c_str() << endl;
}
