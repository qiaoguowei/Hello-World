#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <boost/scope_exit.hpp>

using namespace std;
const char *TmpFile = "./.tmpfile.lock";

int singleton(const char *lock_file, int& fd)
{
	int rv;

	fd = open(lock_file, O_WRONLY | O_CREAT, 0644);
	if(fd == -1)
	{
		cout << "open file failed." << endl;
		return -2;
	}
	rv = flock(fd, LOCK_EX | LOCK_NB);
	if(rv == -1)
	{
		close(fd);
	}

	return rv;
}

int main()
{
	int fd;
	int rv = singleton(TmpFile, fd);
	if(rv == -2)
	{
		exit(-1);
	}
	else if(rv)
	{
		cout << "this process is running." << endl;
		exit(0);
	}
	if(::daemon(0, 0) < 0)
	{
		return -1;
	}

	BOOST_SCOPE_EXIT(&fd)
	{
		close(fd);
	}BOOST_SCOPE_EXIT_END

	while(true)
	{
		cout << "11111" << endl;
		sleep(1);
	}
}
