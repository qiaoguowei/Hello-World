#include <iostream>
#include <cstdio>

#define INT_TO_STR(a) #a
#define TEST(A) "abc" #A "efg"

int main()
{
	std::string str1 = "abc";

	std::string str2 = INT_TO_STR(1);
	std::cout << str2 << std::endl;
	
	std::string str3 = TEST(d);
	std::cout << str3 << std::endl;
}
