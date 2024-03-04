#include <iostream>
#include <cstdio>
#include <sys/types.h> 
#include <sys/socket.h>
#include <cstring>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <boost/filesystem.hpp>

using namespace std;

#define BACK_LOG 10

int main()
{
	const char *SOCKNAME = "./mysock";
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

	if (boost::filesystem::exists(string(SOCKNAME)))
	{
		boost::filesystem::remove(string(SOCKNAME));
	}
	if (bind(sfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) == -1)
	{
		perror("bind()");
		exit(-1);
	}

	if (listen(sfd, BACK_LOG) == -1)
	{
		perror("listen()");
		exit(-1);
	}

	int cfd = accept(sfd, NULL, NULL);
	if (cfd == -1)
	{
		perror("accept()");
		exit(-1);
	}

	while(1)
	{
		memset(buf, 0, sizeof(buf));
		int read_size = read(cfd, buf, sizeof(buf) - 1);
		if (read_size == 0)
		{
			break;
		}
		else if (read_size == -1)
		{
			if (errno == EINTR)
				continue;
			perror("read()");
			exit(-1);
		}
		else
		{
			cout << "recv : " << buf << endl;
		}
	}

	close(cfd);
	close(sfd);

	if (::remove(SOCKNAME))
	{
		perror("remove()");
		return -1;
	}
}





