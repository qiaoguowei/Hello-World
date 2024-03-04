#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

namespace bf = boost::filesystem;

int main()
{
	boost::system::error_code ec;
	bf::path dst("./testDir/2/1");
	if(!bf::exists(dst))
	{
		try
		{
			if(!bf::create_directories(dst, ec))
			{
				std::cout << ec.message() << std::endl;
				return -1;
			}
		}
		catch(boost::filesystem::filesystem_error &e)
		{
			std::cout << e.what() << std::endl;
			return -1;
		}
	}
	return 0;
}
