#include "TNonblockingServerSocket.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define THRIFT_INVALID_SOCKET (-1)

TNonblockingServerSocket::TNonblockingServerSocket(int port)
  : port_(port),
    listenPort_(port),
    serverSocket_(THRIFT_INVALID_SOCKET),
    acceptBacklog_(DEFAULT_BACKLOG),
    sendTimeout_(0),
    recvTimeout_(0),
    retryLimit_(0),
    retryDelay_(0),
    tcpSendBuffer_(0),
    tcpRecvBuffer_(0),
    keepAlive_(false),
    listening_(false)
{
}

TNonblockingServerSocket::TNonblockingServerSocket(int port, int sendTimeout, int recvTimeout)
  : port_(port),
    listenPort_(port),
    serverSocket_(THRIFT_INVALID_SOCKET),
    acceptBacklog_(DEFAULT_BACKLOG),
    sendTimeout_(sendTimeout),
    recvTimeout_(recvTimeout),
    retryLimit_(0),
    retryDelay_(0),
    tcpSendBuffer_(0),
    tcpRecvBuffer_(0),
    keepAlive_(false),
    listening_(false)
{
}

TNonblockingServerSocket::TNonblockingServerSocket(const string& address, int port)
  : port_(port),
    listenPort_(port),
    address_(address),
    serverSocket_(THRIFT_INVALID_SOCKET),
    acceptBacklog_(DEFAULT_BACKLOG),
    sendTimeout_(0),
    recvTimeout_(0),
    retryLimit_(0),
    retryDelay_(0),
    tcpSendBuffer_(0),
    tcpRecvBuffer_(0),
    keepAlive_(false),
    listening_(false)
{
}

TNonblockingServerSocket::TNonblockingServerSocket(const string& path)
  : port_(0),
    listenPort_(0),
    path_(path),
    serverSocket_(THRIFT_INVALID_SOCKET),
    acceptBacklog_(DEFAULT_BACKLOG),
    sendTimeout_(0),
    recvTimeout_(0),
    retryLimit_(0),
    retryDelay_(0),
    tcpSendBuffer_(0),
    tcpRecvBuffer_(0),
    keepAlive_(false),
    listening_(false)
{
}

TNonblockingServerSocket::~TNonblockingServerSocket() {
  close();
}

bool TNonblockingServerSocket::isOpen() const
{
    if (serverSocket_ == THRIFT_INVALID_SOCKET)
        return false;

    if (!listening_)
        return false;

    if (isUnixDomainSocket() && (path_[0] != '\0'))
    {
        struct stat path_info;
        if (::stat(path_.c_str(), &path_info) < 0)
        {
            const std::string vError = "TNonblockingServerSocket::isOpen(): The domain socket path '" + path_ + "' does not exist (yet).";
            std::cerr << vError << std::endl;
            return false;
        }
    }

    return true;
}

void TNonblockingServerSocket::setSendTimeout(int sendTimeout)
{
    sendTimeout_ = sendTimeout;
}

void TNonblockingServerSocket::setRecvTimeout(int recvTimeout)
{
    recvTimeout_ = recvTimeout;
}

void TNonblockingServerSocket::setAcceptBacklog(int accBacklog)
{
    acceptBacklog_ = accBacklog;
}

void TNonblockingServerSocket::setRetryLimit(int retryLimit)
{
    retryLimit_ = retryLimit;
}

void TNonblockingServerSocket::setRetryDelay(int retryDelay)
{
    retryDelay_ = retryDelay;
}

void TNonblockingServerSocket::setTcpSendBuffer(int tcpSendBuffer)
{
    tcpSendBuffer_ = tcpSendBuffer;
}

void TNonblockingServerSocket::setTcpRecvBuffer(int tcpRecvBuffer)
{
    tcpRecvBuffer_ = tcpRecvBuffer;
}

void TNonblockingServerSocket::_setup_sockopts()
{
  int one = 1;
  if (!isUnixDomainSocket())
  {
    if (-1 == setsockopt(serverSocket_,
                         SOL_SOCKET,
                         THRIFT_NO_SOCKET_CACHING,
                         cast_sockopt(&one),
                         sizeof(one)))
    {
      close();
    }
  }

  if (tcpSendBuffer_ > 0)
  {
    if (-1 == setsockopt(serverSocket_,
                         SOL_SOCKET,
                         SO_SNDBUF,
                         cast_sockopt(&tcpSendBuffer_),
                         sizeof(tcpSendBuffer_)))
    {
      int errno_copy = THRIFT_GET_SOCKET_ERROR;
      GlobalOutput.perror("TNonblockingServerSocket::listen() setsockopt() SO_SNDBUF ", errno_copy);
      close();
      throw TTransportException(TTransportException::NOT_OPEN,
                                "Could not set SO_SNDBUF",
                                errno_copy);
    }
  }

  if (tcpRecvBuffer_ > 0)
  {
    if (-1 == setsockopt(serverSocket_,
                         SOL_SOCKET,
                         SO_RCVBUF,
                         cast_sockopt(&tcpRecvBuffer_),
                         sizeof(tcpRecvBuffer_)))
    {
      int errno_copy = THRIFT_GET_SOCKET_ERROR;
      GlobalOutput.perror("TNonblockingServerSocket::listen() setsockopt() SO_RCVBUF ", errno_copy);
      close();
      throw TTransportException(TTransportException::NOT_OPEN,
                                "Could not set SO_RCVBUF",
                                errno_copy);
    }
  }

  struct linger ling = {0, 0};
  if (-1 == setsockopt(serverSocket_, SOL_SOCKET, SO_LINGER, cast_sockopt(&ling), sizeof(ling))) {
    int errno_copy = THRIFT_GET_SOCKET_ERROR;
    GlobalOutput.perror("TNonblockingServerSocket::listen() setsockopt() SO_LINGER ", errno_copy);
    close();
    throw TTransportException(TTransportException::NOT_OPEN, "Could not set SO_LINGER", errno_copy);
  }

  if (-1 == setsockopt(serverSocket_, SOL_SOCKET, SO_KEEPALIVE, const_cast_sockopt(&one), sizeof(one))) {
    int errno_copy = THRIFT_GET_SOCKET_ERROR;
    GlobalOutput.perror("TNonblockingServerSocket::listen() setsockopt() SO_KEEPALIVE ", errno_copy);
    close();
    throw TTransportException(TTransportException::NOT_OPEN,
      "Could not set TCP_NODELAY",
      errno_copy);
  }

  int flags = THRIFT_FCNTL(serverSocket_, THRIFT_F_GETFL, 0);
  if (flags == -1) {
    int errno_copy = THRIFT_GET_SOCKET_ERROR;
    GlobalOutput.perror("TNonblockingServerSocket::listen() THRIFT_FCNTL() THRIFT_F_GETFL ", errno_copy);
    close();
    throw TTransportException(TTransportException::NOT_OPEN,
                              "THRIFT_FCNTL() THRIFT_F_GETFL failed",
                              errno_copy);
  }

  if (-1 == THRIFT_FCNTL(serverSocket_, THRIFT_F_SETFL, flags | THRIFT_O_NONBLOCK)) {
    int errno_copy = THRIFT_GET_SOCKET_ERROR;
    GlobalOutput.perror("TNonblockingServerSocket::listen() THRIFT_FCNTL() THRIFT_O_NONBLOCK ", errno_copy);
    close();
    throw TTransportException(TTransportException::NOT_OPEN,
                              "THRIFT_FCNTL() THRIFT_F_SETFL THRIFT_O_NONBLOCK failed",
                              errno_copy);
  }
}












