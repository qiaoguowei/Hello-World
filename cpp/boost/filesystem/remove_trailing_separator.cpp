#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;

int main()
{
	wstring dir = L"/opt/skyguard/ucs/";
	boost::filesystem::wpath work_dir(dir);
	/*
	 *	如果路径是个目录，最后一个字节是 '/'，则删除'/'
	 * */
	wstring work_directory = work_dir.remove_trailing_separator().wstring();

	string work_directory2(work_directory.begin(), work_directory.end());
	cout << work_directory2 << endl;
}
