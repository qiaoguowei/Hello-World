#include <iostream>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>

const std::string FileName = "./test.log";

int main()
{
	int nIndex = 0;
	int fd = open(FileName.c_str(), O_CREAT | O_APPEND | O_RDWR, 0664);
	if(fd <= 0)
	{
		printf("open file fail\n");
		return -1;
	}
	while(nIndex++ < 30)
	{	//LOCK_EX一个进程只能持有一个排他锁，LOCK_NB非阻塞模式
		if(0 == flock(fd, LOCK_EX))// | LOCK_NB))
		{
			dprintf(fd, "do something %d, %d\n", getpid(), nIndex);
			flock(fd, LOCK_UN);
			sleep(1);
			//flock(fd, LOCK_UN);
		}
	}
#if 0
	if(0 == flock(fd, LOCK_EX))//| LOCK_NB))
	{
		while(nIndex++ < 30)
		{
			dprintf(fd, "do something %d, %d\n", getpid(), nIndex);
		}
	}
	flock(fd, LOCK_UN);
#endif
	close(fd);
	return 0;
}
