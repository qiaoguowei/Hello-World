#include <iostream>
#include <boost/algorithm/string.hpp>

int main()
{
	std::string str1 = "aa+aa+bb+bb";

	boost::algorithm::replace_all(str1, "+", "%2B");
	std::cout << str1 << std::endl;
}
