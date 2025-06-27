#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 9001
#define SEND_DATA "helloworld"
/*
        在Linux上一个socket没有建立连接之前，用select函数检测其是否可写，我们也会得到可写的结果，所以上述流程并不适用于 Linux。
        Linux上正确的做法是，connect之后，不仅要调用 select检测是否可写，还要调用 getsockopt检测此时 socket是否出错，
    通过错误码来检测和确定是否连接上，错误码为0时表示连接上，反之表示未连接上。完整的代码如下：
 */

int main()
{
    //创建一个socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    //将clientfd设置为非阻塞模式
    int old_socket_flag = fcntl(clientfd, F_GETFL, 0);
    int new_socket_flag = old_socket_flag | O_NONBLOCK;
    if (fcntl(clientfd, F_SETFL, new_socket_flag) == -1)
    {
        close(clientfd);
        std::cout << "set socket to nonblock error." << std::endl;
        return -1;
    }

    //2.连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);

    while (true)
    {
        int ret = connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        if (ret == 0)
        {
            std::cout << "connect to server successfully." << std::endl;
            close(clientfd);
            return 0;
        }
        else if (ret == -1)
        {
            if (errno == EINTR)
            {
                //connect 动作被信号中断，重试connect
                std::cout << "connecting interruptted by sinal, try again." << std::endl;
                continue;
            }
            else if (errno == EINPROGRESS)
            {
                //连接正在尝试中
                break;
            }
            else
            {
                //真的出错了
                close(clientfd);
                return -1;
            }
        }
    }

    fd_set writeset;
    FD_ZERO(&writeset);
    FD_SET(clientfd, &writeset);
    struct timeval tv;
    tv.tv_sec = 3;
    tv.tv_usec = 0;
    //3.调用select函数判断socket是否可写
    if (select(clientfd + 1, NULL, &writeset, NULL, &tv) != 1)
    {
        std::cout << "[select] connect to server error." << std::endl;
        close(clientfd);
        return -1;
    }

    int err;
    socklen_t len = static_cast<socklen_t>(sizeof(err));
    //4.调用getsockopt检测此时socket是否出错
    if (::getsockopt(clientfd, SOL_SOCKET, SO_ERROR, &err, &len) < 0)
    {
        close(clientfd);
        return -1;
    }

    if (err == 0)
        std::cout << "4.connect to server successfully." << std::endl;
    else
        std::cout << "4.connect to server error." << std::endl;

    close(clientfd);

    return 0;
}
