#include <iostream>
#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
namespace bf = boost::filesystem;

int main()
{
	bf::path mpath("/home/qgw/program/cplusplus/boost/filesystem/make.sh");
	try
	{
		cout << bf::file_size(mpath.string()) << endl;
	}
	catch(bf::filesystem_error &e)
	{
		cerr << e.what() << endl;
	}
}
