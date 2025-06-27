#include <iostream>
#include <boost/filesystem.hpp>
#include <unistd.h>
#include <sys/types.h>

namespace bf = boost::filesystem;
using std::cout;
using std::endl;

int main()
{
	try
	{
		if(bf::exists("/proc/self/exe"))
			cout << boost::filesystem::read_symlink("/proc/self/exe").parent_path().string() << endl;
		if(bf::exists("/proc/curproc/file"))
			cout << boost::filesystem::read_symlink("/proc/curproc/file").parent_path().string() << endl;
		if(bf::exists("/proc/curproc/exe"))
			cout << boost::filesystem::read_symlink("/proc/curproc/exe").parent_path().string() << endl;
        cout << "11111" << endl;
	}
	catch(std::exception& e)
	{
		cout << "error : " << e.what() << endl;
	}
}
