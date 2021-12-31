#include <iostream>

int main()
{
	std::string str1 = "abcdefghigklmnopqistuvwxyz";

	std::string str2 = str1.substr(8, 10);

	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;
}
