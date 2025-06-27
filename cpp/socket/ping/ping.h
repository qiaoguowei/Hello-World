#ifndef _QGW_PING_H
#define _QGW_PING_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <functional>
#include <vector>
#include <poll.h>


#define BUFSIZE 1500 

class ICMPClient
{
public:
    ICMPClient() {}

    void proc_v4(char *, ssize_t, struct msghdr *, struct timeval *);
    void send_v4(void);
    void readloop(void);
    void tv_sub(struct timeval *, struct timeval *);
    struct addrinfo *Host_serv(const char *host, const char *serv);
    std::string Sock_ntop_host(const struct sockaddr *sa, socklen_t salen);
    //static void sig_alrm(int signo);

    struct Proto
    {
        struct sockaddr  *sasend; /* sockaddr{} for send, from getaddrinfo */
        struct sockaddr  *sarecv; /* sockaddr{} for receiving */
        socklen_t salen; /* length of sockaddr{}s */
        int icmpproto; /* IPPROTO_xxx value for ICMP */
    };


    Proto   *pr;
    char    sendbuf[BUFSIZE];
    int     datalen = 56;    /* # bytes of data following ICMP header */
    char    *host;
    int     nsent;      /* add 1 for each sendto() */
    pid_t   pid;
    int     sockfd;
    int     verbose;
};




#endif
