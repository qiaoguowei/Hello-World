#include <iostream>
#include <boost/regex.hpp>

int main()
{
	//std::string value;
	std::string key = "Host";
	std::string regStr = ".*" + key + "=(.+?);.*";
	boost::regex exp(regStr, boost::regex::perl|boost::regex::icase);
	boost::cmatch what;
	if(boost::regex_match("Host=172.22.70.160;port=10000;schema=testdb;", what, exp))
	{
		for(int i = 0; i < what.size(); i++)
			std::cout << what[i] << std::endl;
	}

	//std::cout << value << std::endl;
}
