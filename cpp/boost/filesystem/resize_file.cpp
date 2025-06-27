#include <iostream>
#include <boost/filesystem.hpp>
#include <string>

using namespace std;

int main()
{
	string filename = "./test_resize_file.txt";
	int mSize = boost::filesystem::file_size(filename);

	//boost::filesystem::resize_file(filename, mSize - 10);//减少文件的大小会相应的删从文件末尾开始除文件的内容
	
	boost::filesystem::resize_file(filename, mSize + 10);//增加文件的大小会从文件的末尾加一些符号
}
