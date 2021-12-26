#include <iostream>
#include <boost/algorithm/string/replace.hpp>

int main()
{
	std::string str1 = "asdfg.bin";
	std::string str2 = boost::algorithm::ireplace_last_copy(str1, ".bin", ".key");
	std::cout << "str1 = " << str1 << std::endl;
	std::cout << "str2 = " << str2 << std::endl;
}
