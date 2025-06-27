#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <errno.h>

#define INVALID_FD -1

int main(int argc, char *argv[])
{
    //创建一个监听socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == INVALID_FD)
    {
        std::cout << "create listen socket error." << std::endl;
        return -1;
    }

    //将监听socket设置为非阻塞的
    int old_socket_flag = fcntl(listenfd, F_GETFL, 0);
    int new_socket_flag = old_socket_flag | O_NONBLOCK;
    if (fcntl(listenfd, F_SETFL, new_socket_flag) == -1)
    {
        close(listenfd);
        std::cout << "set listenfd to nonblock error." << std::endl;
        return -1;
    }

    //复用地址和端口号
    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (char *)&on, sizeof(on));

    //初始化服务器地址
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(9001);
    if (bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout << "bind listen socket error." << std::endl;
        close(listenfd);
        return -1;
    }

    //启动监听
    if (listen(listenfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error " << std::endl;
        close(listenfd);
        return -1;
    }

    std::vector<pollfd> fds;
    pollfd listen_fd_info;
    listen_fd_info.fd = listenfd;
    listen_fd_info.events = POLLIN;
    listen_fd_info.revents = 0;
    fds.push_back(listen_fd_info);

    //是否存在无效的fd标志
    bool exist_invalid_fd;
    int n;
    while (true)
    {
        exist_invalid_fd = false;
        n = poll(&fds[0], fds.size(), 1000);
        if (n < 0)
        {
            //被信号中断
            if (errno == EINTR)
                continue;

            //出错，退出循环
            std::perror("select()");
            break;
        }
        else if (n == 0)
        {
            std::cout << "timeout..." << std::endl;
            continue;
        }

        int size = fds.size();
        for (size_t i = 0; i < size; ++i)
        {
            //事件可读
            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == listenfd)
                {
                    //监听socket，接受新连接
                    struct sockaddr_in clientaddr;
                    socklen_t clientaddrlen = sizeof(clientaddr);
                    //接受客户端连接并将产生的clientfd加入fds集合中
                    int clientfd  = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
                    if (clientfd != -1)
                    {
                        //将客户端socket设置为非阻塞的
                        int old_socket_flag = fcntl(clientfd, F_GETFL, 0);
                        int new_socket_flag = old_socket_flag | O_NONBLOCK;
                        if (fcntl(clientfd, F_SETFL, new_socket_flag) == -1)
                        {
                            close(clientfd);
                            std::cout << "set clientfd to nonblock error." << std::endl;
                        }
                        else
                        {
                            struct pollfd client_fd_info;
                            client_fd_info.fd = clientfd;
                            client_fd_info.events = POLLIN;
                            client_fd_info.revents = 0;
                            fds.push_back(client_fd_info);
                            std::cout << "new client accepted, clientfd: " << clientfd << std::endl;
                        }
                    }
                }
                else
                {
                    //在socket可读时获取当前接受缓冲区中的字节数
                    //对于Linux的ioctl函数是个例外，必须将bytesToRecv初始化为0，才能在ioctl函数调用成功后得到正确的结果
                    ulong bytesToRecv = 0;
                    if (ioctl(fds[i].fd, FIONREAD, &bytesToRecv) == 0)
                    {
                        std::cout << "bytesToRecv: " << bytesToRecv << std::endl;
                    }

                    //普通clientfd，收取数据
                    char buf[64] = {0};
                    int m = recv(fds[i].fd, buf, 64, 0);
                    if (m <= 0)
                    {
                        if (errno != EINTR && errno != EWOULDBLOCK)
                        {
                            //出错或对端关闭了连接，关闭对应的clientfd，并设置无效标志位
                            std::cout << "client disconnected, clientfd: " << fds[i].fd << std::endl;
                            close(fds[i].fd);
                            fds[i].fd = INVALID_FD;
                            exist_invalid_fd = true;
                        }
                    }
                    else
                    {
                        std::cout << "recv from client: " << buf << ", clientfd: " << fds[i].fd << std::endl;
                    }
                }
            }
            else if (fds[i].revents & POLLERR)
            {
                std::cout << "POLLERR" << std::endl;
            }
        }//end out-of-loop

        if (exist_invalid_fd)
        {
            for (std::vector<pollfd>::iterator iter = fds.begin(); iter != fds.end(); )
            {
                if (iter->fd = INVALID_FD)
                    fds.erase(iter);
                else
                    ++iter;
            }
        }
    }//end while-loop

    //关闭所有socket
    for (std::vector<pollfd>::iterator iter = fds.begin(); iter != fds.end(); ++iter)
        close(iter->fd);

    return 0;
}
