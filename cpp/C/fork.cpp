#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	signal(SIGCHLD, SIG_IGN);
	if(0 != fork())
	{
		std::cout << getpid() << std::endl;
		return 0;
	}

	int mPid = getpid();
	std::cout << mPid << std::endl;
	return 0;
}
