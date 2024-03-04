#include <iostream>
#include <cstring>
#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

//int poll(struct pollfd *fds, nfds_t nfds, int timeout);
/*
 *nfds_t : typedef unsigned long int nfds_t;
 *timeout : 超时时间，单位毫秒
 *struct pollfd
 * {
 *	int fd;
 *	short events;
 *	short revents;
 * };
 *
 * events由开发者设置，revents在poll函数返回时由内核设置，说明该fd发生了什么事件
 * POLLIN, POLLOUT, ...
 *
 *
 * */

#define INVALID_FD -1

int main(int argc, char *argv[])
{
	//创建一个监听socket
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == INVALID_FD)
	{
		std::cout << "create listen socket error." << std::endl;
		return -1;
	}

	//将监听socket设置为非阻塞的
	int oldSocketFlag = fcntl(listenfd, F_GETFL, 0);
	int newSocketFlag = oldSocketFlag | O_NONBLOCK;
	if(fcntl(listenfd, F_SETFL, newSocketFlag) == -1)
	{
		close(listenfd);
		std::cout << "set listenfd to nonblock error." << std::endl;
		return -1;
	}

	//复用地址和端口
	int on = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (char *)&on, sizeof(on));
#if 0
	//初始化服务器的地址
	struct sockaddr_in bindaddr;
	bindaddr.sin_family = AF_INET;
	bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bindaddr.sin_port = htons(9002);
	if(bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
	{
		std::cout << "bind listen socket error." << std::endl;
		close(listenfd);
		return -1;
	}

	//启动监听
	if(listen(listenfd, SOMAXCONN) == -1)
	{
		std::cout << "listen error." << std::endl;
		close(listenfd);
		return -1;
	}
#endif
	struct sockaddr_in bindaddr;
	bindaddr.sin_family = AF_INET;
	//bindaddr.sin_addr.s_addr = htonl("172.22.37.1");
    inet_pton(AF_INET, "172.22.37.1", &bindaddr.sin_addr);
	bindaddr.sin_port = htons(9002);
    int xxx = connect(listenfd, (struct sockaddr*)&bindaddr, sizeof(struct sockaddr));
    std::cout << "xxx : " << xxx << std::endl;

	std::vector<pollfd> fds;
	pollfd listen_fd_info;
	listen_fd_info.fd = listenfd;
	listen_fd_info.events = POLLOUT;
	listen_fd_info.revents = 0;
	fds.push_back(listen_fd_info);

	//是否存在无效的fd标志
	bool exist_invalid_fd;
	int n;

	while(true)
	{
		exist_invalid_fd = false;
		n = poll(&fds[0], fds.size(), 1000);
		if(n < 0)
		{
			//被信号中断
			if(errno == EINTR)
				continue;
			//出错，退出
			break;
		}
		else if(n == 0)
		{
			//超时,继续
			continue;
		}

		for(size_t i = 0; i < fds.size(); ++i)
		{
			if(fds[i].revents & POLLOUT)
			{
                std::cout << "POLLOUT" << std::endl;
                break;
			}
			else if(fds[i].revents & POLLERR)
			{
				//暂不处理
                std::cout << "POLLERR" << std::endl;
			}
		}//end outer-for-loop

		if(exist_invalid_fd)
		{
			//统一清理
			for(auto iter = fds.begin(); iter != fds.end();)
			{
				if(iter->fd == INVALID_FD)
					iter = fds.erase(iter);
				else
					++iter;
			}
		}
        break;
	}//end while-loop

	for(auto iter = fds.begin(); iter != fds.end(); ++iter)
	{
		close(iter->fd);
	}

	return 0;
}









