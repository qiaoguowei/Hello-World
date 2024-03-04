#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

#define LISTENQ 1024
#define MAXLINE 1024

int main(int argc, char *argv[])
{
    int listenfd;
    int connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "socket error." << std::endl;
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9001);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cout << "bind error." << std::endl;
        return -1;
    }

    if (listen(listenfd, LISTENQ) < 0)
    {
        std::cout << "listen error." << std::endl;
        return -1;
    }

    while (1)
    {
        connfd = accept(listenfd, (sockaddr *)NULL, NULL);
        if (connfd < 0)
        {
            std::cout << "accept error." << std::endl;
            break;
        }

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if (write(connfd, buff, strlen(buff)) < 0)
        {
            std::cout << "write error." << std::endl;
            break;
        }

        close(connfd);
    }

    close(listenfd);
}


