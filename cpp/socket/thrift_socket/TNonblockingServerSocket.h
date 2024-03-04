#ifndef _TNONBLOCKINGSERVERSOCKET_H
#define _TNONBLOCKINGSERVERSOCKET_H

#include "TNonblockingServerTransport.h"
#include <functional>

#define THRIFT_SOCKET int

class TNonblockingServerSocket : public TNonblockingServerTransport
{
public:
    typedef std::function<void(THRIFT_SOCKET fd)> socket_func_t;

    const static int DEFAULT_BACKLOG = 1024;

    TNonblockingServerSocket(int port);

    TNonblockingServerSocket(int port, int sendTimeout, int recvTimeout);

    TNonblockingServerSocket(const std::string& address, int port);

    TNonblockingServerSocket(const std::string& path);

    ~TNonblockingServerSocket() override;

    bool isOpen() const;

    void setSendTimeout(int sendTimeout);
    void setRecvTimeout(int recvTimeout);

    void setAcceptBacklog(int accBacklog);

    void setRetryLimit(int retryLimit);
    void setRetryDelay(int retryDelay);

    void setKeepAlive(bool keepAlive) { keepAlive_ = keepAlive; }

    void setTcpSendBuffer(int tcpSendBuffer);
    void setTcpRecvBuffer(int tcpRecvBuffer);

    void setListenCallback(const socket_func_t& listenCallback) { listenCallback_ = listenCallback; }

    void setAcceptCallback(const socket_func_t& acceptCallback) { acceptCallback_ = acceptCallback; }

    THRIFT_SOCKET getSocketFD() override { return serverSocket_; }

    int getPort() override;

    int getListenPort() override;

    std::string getPath() const;

    bool isUnixDomainSocket() const;

    void listen() override;

    void close() override;

protected:
    std::shared_ptr<TSocket> acceptImpl() override;
    virtual std::shared_ptr<TSocket> createSocket(THRIFT_SOCKET client);

private:
    void _setup_sockopts();
    void _setup_unixdomain_sockopts();
    void _setup_tcp_sockopts();

    int port_;
    int listenPort_;
    std::string address_;
    std::string path_;
    THRIFT_SOCKET serverSocket_;

    int acceptBacklog_;
    int sendTimeout_;
    int recvTimeout_;
    int retryLimit_;
    int retryDelay_;
    int tcpSendBuffer_;
    int tcpRecvBuffer_;
    bool keepAlive_;
    bool listening_;

    socket_func_t listenCallback_;
    socket_func_t acceptCallback_;
};


#endif //_TNONBLOCKINGSERVERSOCKET_H
