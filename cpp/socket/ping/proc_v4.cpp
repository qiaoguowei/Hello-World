#include "ping.h"


u_short in_cksum(u_short *addr, int len)
{
    register int nleft = len;
    register u_short *w = addr;
    register int sum = 0;
    u_short answer = 0;

    /*
     *      * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     *           * sequential 16 bit words to it, and at the end, fold back all the
     *                * carry bits from the top 16 bits into the lower 16 bits.
     *                     */
    while (nleft > 1)  {
        sum += *w++;
        nleft -= 2;
    }

    /* mop up an odd byte, if necessary */
    if (nleft == 1) {
        *(u_char *)(&answer) = *(u_char *)w ;
        sum += answer;
    }

    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
    sum += (sum >> 16);         /* add carry */
    answer = ~sum;              /* truncate to 16 bits */
    return (answer);
}

void ICMPClient::proc_v4(char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv)
{
    int             hlen1, icmplen;
    double          rtt;
    struct ip       *ip;
    struct icmp     *icmp;
    struct timeval  *tvsend;

    ip = (struct ip *) ptr;     /* start of IP header */
    hlen1 = ip->ip_hl << 2;     /* length of IP header */
    if (ip->ip_p != IPPROTO_ICMP)
    {
        std::cout << "not ICMP" << std::endl;
        return ;                /* not ICMP */
    }

    icmp = (struct icmp *) (ptr + hlen1);   /* start of ICMP header */
    if ( (icmplen = len - hlen1) < 8)
    {
        std::cout << "malformed packet" << std::endl;
        return ;                /* malformed packet */
    }

    if (icmp->icmp_type == ICMP_ECHOREPLY)
    {
        if (icmp->icmp_id != pid)
        {
            std::cout << "not a response to our ECHO_REQUEST" << std::endl;
            return ;            /* not a response to our ECHO_REQUEST */
        }
        if (icmplen < 16)
        {
            std::cout << "not enough data to use" << std::endl;
            return ;            /* not enough data to use */
        }

        tvsend = (struct timeval *) icmp->icmp_data;
        tv_sub(tvrecv, tvsend);
        rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

        printf("%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n",
                icmplen, (Sock_ntop_host(pr->sarecv, pr->salen)).c_str(),
                icmp->icmp_seq, ip->ip_ttl, rtt);
    }
    else if (verbose)
    {
        printf("  %d bytes from %s: type = %d, code = %d\n", 
                icmplen, (Sock_ntop_host(pr->sarecv, pr->salen)).c_str(),
                icmp->icmp_type, icmp->icmp_code);
    }
}

void ICMPClient::tv_sub(struct timeval *out, struct timeval *in)
{
    if ( (out->tv_usec -= in->tv_usec) < 0)
    {
        --out->tv_sec;
        out->tv_usec += 1000000;
    }
    out->tv_sec -= in->tv_sec;
}

void ICMPClient::send_v4()
{
    int         len;
    struct icmp *icmp;

    icmp = (struct icmp *) sendbuf;
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_id = pid;
    icmp->icmp_seq = nsent++;
    memset(icmp->icmp_data, 0xa5, datalen); /* fill with pattern */
    gettimeofday((struct timeval *) icmp->icmp_data, NULL);

    len = 8 + datalen;      /* checksum ICMP header and data */
    icmp->icmp_cksum = 0;
    icmp->icmp_cksum = in_cksum((u_short *) icmp, len);
    char *sendbuf_ptr = sendbuf;

    while (len)
    {
        int res = sendto(sockfd, sendbuf_ptr, len, 0, pr->sasend, pr->salen);
        if (res == -1)
        {
            if (errno == EINTR)
                continue;
            else
            {
                std::cout << "sendto error." << strerror(errno) << std::endl;
                return;
            }
        }
        len -= res;
        sendbuf_ptr += res;
    }
    std::cout << "send success." << std::endl;
}

void ICMPClient::readloop()
{
    int             size;
    char            recvbuf[BUFSIZE];
    char            controlbuf[BUFSIZE];
    struct msghdr   msg;
    struct iovec    iov;
    ssize_t         n = 0;
    struct timeval  tval;

    if ((this->sockfd = socket(pr->sasend->sa_family, SOCK_RAW, pr->icmpproto)) < 0)
    {
        std::cout << "socket() error." << strerror(errno) << std::endl;
        return;
    }
    setuid(getuid());

    size = 60 * 1024;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

    //sig_alrm(SIGALRM);      /* send first packet */
    send_v4();

    iov.iov_base = recvbuf;
    iov.iov_len = sizeof(recvbuf);
    msg.msg_name = pr->sarecv;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = controlbuf;

    std::vector<pollfd> fds;
    pollfd listen_fd_info;
    listen_fd_info.fd = sockfd;
    listen_fd_info.events = POLLIN;
    listen_fd_info.revents = 0;
    fds.push_back(listen_fd_info);
    int poll_res = 0;

    while (1)
    {
        msg.msg_namelen = pr->salen;
        msg.msg_controllen = sizeof(controlbuf);
        poll_res = poll(&fds[0], fds.size(), 5000);
        if (poll_res < 0)
        {
            if (errno == EINTR)
                continue;
            else
            {
                std::cout << "poll() error" << std::endl;
                return;
            }
        }
        else if (poll_res == 0)
        {
            std::cout << "ping() timeout." << std::endl;
            return;
        }

        for(size_t i = 0; i < fds.size(); ++i)
        {
            if (fds[i].revents & POLLIN)
            {
                n = recvmsg(sockfd, &msg, 0);
                if (n < 0)
                {
                    if (errno == EINTR)
                        continue;
                    else
                    {
                        std::cout << "recvmsg error" << std::endl;
                        return;
                    }
                }

                gettimeofday(&tval, NULL);
                proc_v4(recvbuf, n, &msg, &tval);
            }
        }
        break;
    }
}

struct addrinfo * ICMPClient::Host_serv(const char *host, const char *serv)
{
    int             n;
    struct addrinfo hints, *res;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_CANONNAME;  /* always return canonical name */
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;

    if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
    {
        std::cout << "host_serv error for " //<< (host == NULL) ? "(no hostname)" : host 
            //<< (serv == NULL) ? "(no service name)" : serv
            << strerror(n) << std::endl;
        return NULL; 
    }
    return(res);    /* return pointer to first on linked list */
}

std::string ICMPClient::Sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    char str[128] = {0};
    std::string sstr;
    switch (sa->sa_family)
    {
        case AF_INET:
            struct sockaddr_in  *sin = (struct sockaddr_in *) sa;
            if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
                return std::string();
            sstr = str;
            return(sstr);
    }
    return std::string();
}
#if 0
void ICMPClient::sig_alrm(int signo)
{
    send_v4();
    alarm(1);
    return ;
}
#endif















