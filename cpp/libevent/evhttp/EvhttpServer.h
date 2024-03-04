#ifndef _EVHTTPSERVER_H
#define _EVHTTPSERVER_H


#include <iostream>
#include <evhttp.h>
#include <string>

using namespace std;

class EvhttpServer
{
public:
    EvhttpServer();
    ~EvhttpServer();
    bool init(int port, const char *host);
    int service();
    void stop();
    static void SendFileContent(struct evhttp_request *req, void *self);
    static void ParserUrl(struct evhttp_request *req);

private:
    struct event_base *eb_;
    struct evhttp *eh_;
};




#endif

