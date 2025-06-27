#include <iostream>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <cstring>
#include <vector>

#define INVALID_FD -1

int main(int argc, char *argv[])
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == 0)
    {
        std::cout << "create listen socket error." << std::endl;
        return -1;
    }

    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(9001);
    if(bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout << "bind listen socket error." << std::endl;
        close(listenfd);
        return -1;
    }

    if(listen(listenfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error." << std::endl;
        close(listenfd);
        return -1;
    }

    std::vector<int> clientfds;
    int maxfd;

    while(true)
    {
        fd_set readset;
        FD_ZERO(&readset);

        FD_SET(listenfd, &readset);

        maxfd = listenfd;

        int clientfdslength = clientfds.size();
        for(int i = 0; i < clientfdslength; ++i)
        {
            if(clientfds[i] != INVALID_FD)
            {
                FD_SET(clientfds[i], &readset);
                if(maxfd < clientfds[i])
                    maxfd = clientfds[i];
            }
        }

        timeval tm;
        tm.tv_sec = 10;
        tm.tv_usec = 0;

        int ret = select(maxfd + 1, &readset, NULL, NULL, &tm);
        if(ret == -1)
        {
            if(errno != EINTR)
                break;
        }
        else if(ret == 0)
        {
            //select 函数超时，下次继续
            std::cout << "timeout!!!" << std::endl;
            continue;
        }
        else
        {
            //检测到某个socket有事件
            if(FD_ISSET(listenfd, &readset))
            {
                //监听SOCKET的可读事件，表明有新的连接到来
                struct sockaddr_in clientaddr;
                socklen_t clientaddrlen = sizeof(clientaddr);
                int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
                if(clientfd == INVALID_FD)
                {
                    //连接出错，退出程序
                    break;
                }

                //只接受连接，不调用recv收取任何数据
                std::cout << "accept a client connection, fd: " << clientfd << std::endl;

                clientfds.push_back(clientfd);
            }
            else
            {
                //假设对端发来的数据长度不超过63个字符
                char recvbuf[64];
                int clientfdslength = clientfds.size();
                for(int i = 0; i < clientfdslength; ++i)
                {
                    if(clientfds[i] != INVALID_FD && FD_ISSET(clientfds[i], &readset))
                    {
                        memset(recvbuf, 0, sizeof(recvbuf));
                        int length = recv(clientfds[i], recvbuf, 64, 0);
                        if(length <= 0)
                        {
                            std::cout << "recv data error, clientfd : " << clientfds[i] << std::endl;
                            close(clientfds[i]);
                            clientfds[i] = INVALID_FD;
                            continue;
                        }

                        std::cout << "clientfd : " << clientfds[i] << ", recv data : " << recvbuf << std::endl;
                    }
                }
            }
        }
    }

    //关闭所有客户端socket
    int clientfdslength = clientfds.size();
    for(int i = 0; i < clientfdslength; ++i)
    {
        if(clientfds[i] != INVALID_FD)
        {
            close(clientfds[i]);
            clientfds[i] = INVALID_FD;
        }
    }

    close(listenfd);

    return 0;
}








