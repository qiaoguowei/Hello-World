#ifndef _TNONBLOCKINGSERVERTRANSPORT_H
#define _TNONBLOCKINGSERVERTRANSPORT_H

#include <TSocket.h>

class TNonblockingServerTransport
{
    virtual ~TNonblockingServerTransport() = default;

    virtual void listen() {}

    std::shared_ptr<TSocket> accept()
    {
        std::shared_ptr<TSocket> result = acceptImpl();
        if (!result)
        {
            throw std::Exception("accept() may not return nullptr");
        }
        return result;
    }

    virtual THRIFT_SOCKET getSocketFD() = 0;

    virtual int getPort() = 0;

    virtual int getListenPort() = 0;

    virtual void close() = 0;

protected:
    TNonblockingServerTransport() = default;

    virtual std::shared_ptr<TSocket> acceptImpl() = 0;
};



#endif //_TNONBLOCKINGSERVERTRANSPORT_H
