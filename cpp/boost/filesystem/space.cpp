#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

int main()
{
	fs::path mCurrentFolder("/home/qgw/my_github/Hello-World/cpp/boost/filesystem");	
	uint64_t mCurrentFolderSpace = fs::space(mCurrentFolder).available;
	double mGB = mCurrentFolderSpace / 1024.0 / 1024.0 / 1024.0;
	cout << mGB << endl;
}









