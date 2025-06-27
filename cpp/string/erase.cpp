#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;

int main()
{
	string filename = "2222222_333333";
	size_t index = filename.find_last_of("_");
	if (index != std::string::npos)
	{
		uint32_t package_version = boost::lexical_cast<uint32_t>(filename.substr(index+1));
		std::string uuid = filename.erase(index);
		cout << package_version << endl;
		cout << uuid << endl;
	}
}
