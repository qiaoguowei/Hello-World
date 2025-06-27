#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <cstring>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>

using namespace std;

#define BACK_LOG 10

int main()
{
	const char *SOCKNAME = "./mysock";
	const char *send_buf = "client send";
	int sfd;
	struct sockaddr_un addr;
	char buf[1024];

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		perror("socket()");
		exit(-1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKNAME, sizeof(addr.sun_path) - 1);

	if (connect(sfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) == -1)
	{
		perror("connect()");
		exit(-1);
	}

	while(1)
	{
		write(sfd, send_buf, strlen(send_buf));
		sleep(1);
	}

	close(sfd);
}





