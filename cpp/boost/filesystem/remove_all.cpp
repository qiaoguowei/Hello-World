#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;

int main()
{
	string filepath = "./testDir";
	auto x = boost::filesystem::remove_all(filepath);
    std::cout << x << std::endl;
	if (boost::filesystem::exists(filepath))
	{
		cout << "the dictionary already exists." << endl;
		return 0;
	}
	cout << "the dictionary is not exitsts." << endl;
}
