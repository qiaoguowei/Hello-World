#include "Sftp.h"


SftpClient::SftpClient()
    : session(nullptr)
    , sftp_session(nullptr)
    , sftp_handle(nullptr)
    , sockfd(0)
{
    memset(curdir, 0, 2048);
}

bool SftpClient::openConnectByIp(const string& ip, uint16_t port)
{
    struct sockaddr_in dest_addr;

    if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        std::cout << "sftp client, connect server error in create socket." << std::endl;
        return false;
    }

    int on = 1;
    int result = 0;
    result += setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (const char *)&on, sizeof(on));
    int keep_idle = 60;
    int keep_interval = 5;
    int keep_count = 2;
    result += setsockopt(sockfd, SOL_TCP, TCP_KEEPIDLE, (void*)&keep_idle, sizeof(keep_idle));
    result += setsockopt(sockfd, SOL_TCP, TCP_KEEPINTVL, (void*)&keep_interval, sizeof(keep_interval));
    result += setsockopt(sockfd, SOL_TCP, TCP_KEEPCNT, (void*)&keep_count, sizeof(keep_count));

    if (result < 0)
    {
        std::cout << "failed to set keep alive for client socket fd, skip setting." << std::endl;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (-1 == connect(sockfd, (struct sockaddr*)&dest_addr, sizeof(struct sockaddr)))
    {
        std::cout << "sftp client, connect server failed. ip is [" << ip << "], port is [" << port << "]";
        if (sockfd > 0)
        {
            close(sockfd);
            sockfd = 0;
        }
        return false;
    }
}
