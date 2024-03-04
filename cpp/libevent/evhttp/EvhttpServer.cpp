#include "EvhttpServer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <boost/filesystem.hpp>
#include <boost/scope_exit.hpp>

using namespace std;

EvhttpServer::EvhttpServer() : eb_(nullptr), eh_(nullptr)
{
}

bool EvhttpServer::init(int port, const char *host)
{
    eb_ = event_base_new();
    cout << this_thread::get_id() << endl;
    if (eb_ == nullptr)
    {
        cout << "event_base_new() failed." << endl;
        return false;
    }

    eh_ = evhttp_new(eb_);
    if (eh_ == nullptr)
    {
        event_base_free(eb_);
        cout << "evhttp_new() failed." << endl;
        return false;
    }

    evhttp_set_timeout(eh_, -1);

    int ret = evhttp_bind_socket(eh_, host, port);
    if (ret < 0)
    {
        evhttp_free(eh_);
        event_base_free(eb_);
        cout << "evhttp_bind_socket() failed." << endl;
        return false;
    }

    evhttp_set_cb(eh_, "/xxx/v1/file_content", SendFileContent, this);
    //evhttp_set_gencb(eh_, request, nullptr);

    return true;
}

EvhttpServer::~EvhttpServer()
{
    stop();
    if (eh_ != nullptr)
    {
        evhttp_free(eh_);
        eh_ = nullptr;
    }
    if (eb_ != nullptr)
    {
        event_base_free(eb_);
        eb_ = nullptr;
    }
}

void EvhttpServer::stop()
{
    if (eb_ != nullptr)
    {
        event_base_loopbreak(eb_);
        event_base_loopexit(eb_, NULL);
    }
}

int EvhttpServer::service()
{
    if (eb_ == nullptr)
    {
        cout << "service() failed, event_base is nullptr." << endl;
        return -1;
    }
    return event_base_dispatch(eb_);
}

void EvhttpServer::SendFileContent(struct evhttp_request *req, void *self)
{
    EvhttpServer::ParserUrl(req);
    cout << this_thread::get_id() << endl;
    string rbuf;
    string filename = "./NeedToRead.txt";
    if (!boost::filesystem::exists(filename))
    {
        cout << "the file is not exists." << endl;
        return;
    }

    std::ifstream fin(filename.c_str(), std::ifstream::binary);
    if (!fin.is_open())
    {
        cout << "the file open failed." << endl;
        return;
    }
    char rrbuf[1024];
    while (!fin.eof())
    {
        bzero(rrbuf, sizeof(rrbuf));
        fin.read(rrbuf, sizeof(rrbuf) - 1);
        rbuf += rrbuf;
    }

    struct evbuffer *buf = evbuffer_new();
    BOOST_SCOPE_EXIT(&buf)
    {
        if (buf != nullptr)
        {
            cout << "call evbuffer_free()" << endl;
            evbuffer_free(buf);
        }
    }BOOST_SCOPE_EXIT_END

    if (evbuffer_add(buf, rbuf.c_str(), rbuf.size()) != 0)
    {
        cout << "evbuffer_add() failed." << endl;
        return ;
    }

    evhttp_send_reply(req, 200, "OK", buf);
}

void EvhttpServer::ParserUrl(struct evhttp_request *req)
{
    const char *uri = evhttp_request_get_uri(req);
    cout << "evhttp_request_get_uri(), uri : " << uri << endl;

    const char *decoded_uri = evhttp_decode_uri(uri);
    cout << "evhttp_decode_uri(), decoded_uri : " << endl;

    struct evhttp_uri *decoded = NULL;
    const char *path;

    /* Decode the URI */
    decoded = evhttp_uri_parse(uri);
    if (!decoded)
    {
        cout << "It's not a good URI. Sending BADREQUEST" << endl;
        evhttp_send_error(req, HTTP_BADREQUEST, 0);
        return;
    }

    path = evhttp_uri_get_path(decoded);
    if (!path) 
        path = "/";

    cout << "evhttp_uri_get_path(), path : " << path << endl;

    cout << "Header: " << endl;
    struct evkeyvalq *headers;
    struct evkeyval *header;

    headers = evhttp_request_get_input_headers(req);
    for (header = headers->tqh_first; header; header = header->next.tqe_next)
    {
        cout << header->key << " : " << header->value << endl;
    }
    cout << "Header end ---------------------" << endl;
}
















