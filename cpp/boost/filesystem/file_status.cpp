#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
namespace bf = boost::filesystem;

int main()
{
	bf::file_status st = bf::status("/home/qgw/my_github/Hello-World/cpp/boost/filesystem/file_size.cpp");
	bf::perms perm = st.permissions();

	switch(st.type())
	{
		//case bf::status_error :
		//	cout << "获取文件类型出错。" << endl;
		//	break;
		case bf::file_not_found :
			cout << "file is not exists." << endl;
			break;
		case bf::status_unknown :
			cout << "file is exists, but its status is unknown." << endl;
			break;
		case bf::regular_file :
			cout << "file is a regular file." << endl;
			break;
		default :
			break;
	}
	if(perm & bf::owner_read)
	{
		cout << "You can read the file." << endl;
	}
	if(perm & bf::owner_write)
	{
		cout << "You can write the file." << endl;
	}
	if(perm & bf::owner_exe)
	{
		cout << "You can execute the file." << endl;
	}
}
