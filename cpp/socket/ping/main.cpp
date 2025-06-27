#include "ping.h"

ICMPClient icmp_client;

int datalen = 56;


int main(int argc, char *argv[])
{
    int             c;
    struct addrinfo *ai;
    std::string h;

    if (argc < 2)
    {
        std::cout << "argc < 2, quit" << std::endl;
        return -1;
    }

    icmp_client.host = argv[1];
    icmp_client.pid = getpid() & 0xffff;    /* ICMP ID field is 16 bits */


    ai = icmp_client.Host_serv(icmp_client.host, NULL);

    h = icmp_client.Sock_ntop_host(ai->ai_addr, ai->ai_addrlen);

    printf("PING %s (%s): %d data bytes\n",
            ai->ai_canonname ? ai->ai_canonname : h.c_str(),
            h.c_str(), datalen);

    if (ai->ai_family == AF_INET)
    {
        ICMPClient::Proto icmp_pr = {NULL, NULL, 0, IPPROTO_ICMP};
        icmp_client.pr = &icmp_pr;
    }
    else
    {
        std::cout << "unknown address family " <<  ai->ai_family << std::endl;
        return -1;
    }

    icmp_client.pr->sasend = ai->ai_addr;
    icmp_client.pr->sarecv = (sockaddr*)calloc(1, ai->ai_addrlen);
    icmp_client.pr->salen = ai->ai_addrlen;
    //icmp_client.send_v4();

    icmp_client.readloop();

    return 0;
}
