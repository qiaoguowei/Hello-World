#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iterator>
#include <algorithm>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <unistd.h>

using namespace std;

bool getIpByHost(const std::string host, std::vector<std::string>& ip)
{
#if 0
    bool isIP = true;

    for (auto c : host)
    {
        if (c == '.')
            continue;
        if (c <= '9' && c >= '0')
            continue;
        isIP = false;
        break;
    }

    if (isIP)
    {
        ip.push_back(host);
        return true;
    }
#endif

    struct addrinfo *result = nullptr;
    struct addrinfo *ptr = nullptr;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_ADDRCONFIG;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;
#if 0
    std::cout << "AF_INET = " << AF_INET << std::endl;
    std::cout << "SOCK_RAW = " << SOCK_RAW << std::endl;
    std::cout << "IPPROTO_ICMP = " << IPPROTO_ICMP << std::endl;
#endif

    if (getaddrinfo(host.c_str(), 0, &hints, &result) != 0)
    {
        std::cout << "errno: " << errno << ", explain: " << strerror(errno) << std::endl;
        return false;
    }

    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
    {
        switch(ptr->ai_family)
        {
            case AF_UNSPEC:
                break;
            case AF_INET:
                ip.push_back(inet_ntoa(((struct sockaddr_in *)(ptr->ai_addr))->sin_addr));
            case AF_INET6:
                break;
        }
    }
    freeaddrinfo(result);

    return ip.size() > 0;
}

bool getIpByHostTcp(const std::string host, std::vector<std::string>& ip)
{
    struct addrinfo *result = nullptr;
    struct addrinfo *ptr = nullptr;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(host.c_str(), 0, &hints, &result) != 0)
    {
        std::cout << "errno: " << errno << ", explain: " << strerror(errno) << std::endl;
        return false;
    }

    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
    {
        switch(ptr->ai_family)
        {
            case AF_UNSPEC:
                break;
            case AF_INET:
                ip.push_back(inet_ntoa(((struct sockaddr_in *)(ptr->ai_addr))->sin_addr));
            case AF_INET6:
                break;
        }
    }
    freeaddrinfo(result);

    return ip.size() > 0;
}

int main(int argc, char *argv[])
{
    string host = argv[1];
    while(1)
    {
        std::vector<std::string> ip;
        if (!getIpByHost(host, ip))
        {
            cout << "icmp error." << endl;
        }
        //res_init();

        cout << "icmp: "<< ip.size() << endl;
        std::copy(ip.cbegin(), ip.cend(), std::ostream_iterator<std::string>(cout, "\n"));

        std::vector<std::string> tcp_ip;
        if (!getIpByHost(host, tcp_ip))
        {
            cout << "tcp error." << endl;
        }
        cout << "tcp: " << tcp_ip.size() << endl;
        std::copy(tcp_ip.cbegin(), tcp_ip.cend(), std::ostream_iterator<std::string>(cout, "\n"));

        sleep(5);
    }
}









