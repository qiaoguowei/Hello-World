#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main()
{
	std::string pure_wildcard_string = "[\\?\\*]+";
	boost::regex re(pure_wildcard_string, boost::regex::perl|boost::regex::icase|boost::regex::nosubs);
	std::string str1 = "????";
	std::string str2 = "*****";
	std::string str3 = "?**?";
	std::string str4 = "a?*b";

	std::cout << str1 << " : " << boost::regex_match(str1, re) << std::endl;
	std::cout << str2 << " : " << boost::regex_match(str2, re) << std::endl;
	std::cout << str3 << " : " << boost::regex_match(str3, re) << std::endl;
	std::cout << str4 << " : " << boost::regex_match(str4, re) << std::endl;
}
