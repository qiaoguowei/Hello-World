#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int m_getpid()
{
	FILE *fp = popen("pidof dddd", "r");
	if(fp == NULL)
	{
		std::cout << "can not get pid of dddd." << std::endl;
		return -1;
	}
	char strPid[32] = {0};
	fgets(strPid, sizeof(strPid) - 1, fp);
	int mPid = atoi(strPid);
	pclose(fp);
	return mPid;
}

int main(int argc, char *argv[])
{
	int pid = m_getpid();
	std::cout << pid << std::endl;
	if(pid == -1 || pid == 0)
		return -1;
	for(int i = 0; i < 3; ++i)
	{
		sleep(1);
		int ret = ::kill((pid_t)pid, 9);
		if(-1 == ret)
		{
			std::cout << ret << std::endl;
			if(errno == ESRCH)
			{
				std::cout << "the process is not exists." << std::endl;
			}
			break;
		}
	}
}
