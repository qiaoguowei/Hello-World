#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	string file_path = "./file_of_open.txt";
	int fd = -1;

	while(fd < 0)
	{
		fd = ::open(file_path.c_str(), O_RDWR | O_CLOEXEC);
		if (fd == -1)
		{
			if (EINTR == errno)
				continue;
			perror("open()");
			return -1;
		}
	}

	pid_t mpid = fork();
	if (mpid < 0)
	{
		perror("fork()");
		exit(-1);
	}
	else if (mpid == 0)
	{
		if (fd >= 0)
		{
			if (::write(fd, "Hello", 5) == -1)
			{
				perror("write()");
				exit(-1);
			}
		}
		exit(0);
	}

	int status;
	waitpid(-1, &status, 0);
	close(fd);
	exit(0);
}







