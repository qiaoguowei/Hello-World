#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>

#define MAXLINE 1023

int main(int argc, char *argv[])
{
    int sockfd;
    int n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in6 servaddr;

    if (argc != 2)
    {
        std::cerr << "usage: a.out <IPaddress>" << std::endl;
        return -1;
    }

    if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "socket() error." << std::endl;
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(9001);
    if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
    {
        std::cout << "inet_pton() error for " << argv[1] << std::endl;
        return -1;
    }

    if (connect(sockfd, (sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        std::cout << "connet error." << std::endl;
        return -1;
    }

    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
        {
            std::cout << "fputs error." << std::endl;
            return -1;
        }
    }

    if (n < 0)
    {
        std::cout << "read error." << std::endl;
        return -1;
    }

    return 0;
}
