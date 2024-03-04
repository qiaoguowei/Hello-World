#include <iostream>
#include <string>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>

using namespace std;

class FileMapping
{
public:
	FileMapping(const std::string& fileName);
	~FileMapping();
	int getHandle() { return fd; }

	boost::interprocess::mapping_handle_t get_mapping_handle() const
	{
		return boost::interprocess::ipcdetail::mapping_handle_from_file_handle((boost::interprocess::file_handle_t)(fd));
	}

private:
	void openExistingFile();

	std::string mFileName;
	int fd;
	uint64_t mSize;
};

FileMapping::FileMapping(const std::string& fileName)
	: mFileName(fileName)
	, fd(-1)
	, mSize(0)
{
	openExistingFile();
}

FileMapping::~FileMapping()
{
	if (fd != -1)
	{
		close(fd);
		fd = -1;
	}
}

void FileMapping::openExistingFile()
{
	if (!boost::filesystem::exists(mFileName))
	{
		cout << "the file [" << mFileName << "] is not exists." << endl;
		return ;
	}
	if (boost::filesystem::is_directory(mFileName))
	{
		cout << "this file is a directory." << endl;
		return;
	}
	//mSize = boost::filesystem::file_size(mFileName);
	boost::filesystem::resize_file(mFileName, 100);

	fd = ::open(mFileName.c_str(), O_RDWR);
	if (fd == -1)
	{
		cout << "open file failed." << endl;
		return;
	}

}

int main()
{
	try
	{
		FileMapping mFile("./file_mapped_region.txt");
		boost::interprocess::mapped_region region(mFile, boost::interprocess::read_write, 0, 100); 
		char *p = static_cast<char *>(region.get_address());

		sprintf(p, "abcdefghigklmn\n");
	}
	catch(std::exception& e)
	{
		cout << e.what() << endl;
	}
}








