#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <boost/filesystem.hpp>

int main()
{
	pid_t pid = ::getpid();
	char linkname[64];
	snprintf(linkname, sizeof(linkname), "/proc/%i/exe", pid);

	char buf[256];
	memset(buf, 0, sizeof(buf));

	int ret = ::readlink(linkname, buf, sizeof(buf) - 1);
	if(ret == -1)
	{
		perror("readlink()");
		return -1;
	}

	boost::filesystem::path dir(buf);
	std::cout << dir.parent_path().string() << std::endl;
}
