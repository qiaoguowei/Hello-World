#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <cstring>
#include <string>
#include <unistd.h>

#define MAXLEN 1023

using namespace std;

struct addrinfo *host_serv(const char *host, const char *serv, int family, int socktype)
{
    int n;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_CANONNAME; //always return canonical name
    hints.ai_family = family; //AF_UNSPEC, AF_INET, AP_INET6, etc.
    hints.ai_socktype = socktype; //0, SOCK_STREAM, SOCK_DGRAM, etc.

    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
    {
        cout << gai_strerror(n) << endl;
        return NULL;
    }

    return res;
}

int tcp_connect(const char *host, const char *serv)
{
    int sockfd, n;
    struct addrinfo hints, *res, *ressave;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
    {
        cout << "tcp_connect - getaddrinfo error: " << gai_strerror(n) << endl;
        return -1;
    }
    ressave = res;

    do
    {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;

        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;

        close(sockfd);
    } while ((res = res->ai_next) != NULL);

    if (res == NULL)
    {
        cout << "error -------" << endl;
        return -1;
    }

    return sockfd;
}

int main(int argc, char *argv[])
{
    int sockfd, n;
    char recvline[MAXLEN + 1];
    socklen_t len;
    struct sockaddr_storage ss;

    if (argc != 3)
    {
        cout << "param is too little." << endl;
        return -1;
    }

    sockfd = tcp_connect(argv[1], argv[2]);

    len = sizeof(ss);

    memset(recvline, 0, sizeof(recvline));
    while ((n = read(sockfd, recvline, MAXLEN)) > 0)
    {
        cout << recvline << endl;
        memset(recvline, 0, sizeof(recvline));
    }

    return 0;
}














