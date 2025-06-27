#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid = getpid();
	std::cout << pid << std::endl;
	for(int i = 0; i < 20; ++i)
	{
		std::cout << i << std::endl;
		sleep(1);
	}
}
