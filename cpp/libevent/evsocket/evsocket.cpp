#include <iostream>
#include <string>
#include <event2/event.h>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>

using namespace std;

void client_cb(evutil_socket_t s, short w, void *arg)
{
    cout << "client:" << this_thread::get_id() << endl;
    cout << ". . . " << w << flush;
    event *ev = (event *)arg;
    if (w & EV_TIMEOUT)
    {
        cout << "timeout" << endl;
        //event_free(ev);
        //evutil_closesocket(s);
        return;
    }
    else if (w & EV_CLOSED)
    {
        cout << "close fd." << endl;
        event_free(ev);
        evutil_closesocket(s);
        return;
    }

    char buf[1024] = {0};
    int len = recv(s, buf, sizeof(buf)-1, 0);
    if (len > 0)
    {
        cout << buf << flush;
        send(s, "ok", 2, 0);
    }
    else
    {
        //需要清理event
        cout << "close fd." << endl;
        event_free(ev);
        evutil_closesocket(s);
    }

}

void listen_cb(evutil_socket_t s, short w, void *arg)
{
    cout << "listen_cb " << this_thread::get_id() << endl;
    sockaddr_in sin;
    socklen_t size = sizeof(sin);
    //读取连接信息
    evutil_socket_t client = accept(s, (sockaddr *)&sin, &size);
    char ip[16] = {0};
    evutil_inet_ntop(AF_INET, &sin.sin_addr, ip, sizeof(ip)-1);
    cout << "client ip is " << ip << endl;;

    //客户端
    event_base *base = (event_base *)arg;
    //event *ev = event_new(base, client, EV_READ | EV_PERSIST, client_cb, event_self_cbarg());
    //边缘触发
    event *ev = event_new(base, client, EV_READ | EV_CLOSED | EV_PERSIST | EV_ET, client_cb, event_self_cbarg());
    //event *ev = event_new(base, client, EV_READ | EV_PERSIST | EV_ET, client_cb, event_self_cbarg());
    timeval t = {10, 0};
    event_add(ev, &t);
}

int main()
{
    event_base *base = event_base_new();
    cout << event_base_get_method(base) << endl;

    //event 服务器
    cout << "test event server" << endl;

    evutil_socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <= 0)
    {
        cout << "socket error: " << strerror(errno) << endl;
        return -1;
    }
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9001);

    //设置地址复用，和非阻塞
    evutil_make_socket_nonblocking(sock);
    evutil_make_listen_socket_reuseable(sock);

    int re = ::bind(sock, (sockaddr *)&sin, sizeof(sin));
    if (re != 0)
    {
        cout << "bind error: " << strerror(errno) << endl;
        return -1;
    }

    listen(sock, 10);

    //开始接受连接事件
    //默认水平触发
    event *ev = event_new(base, sock, EV_READ | EV_PERSIST, listen_cb, base);
    if (ev == NULL)
    {

    }
    event_add(ev, 0);

    event_base_dispatch(base);
    evutil_closesocket(sock);
    event_base_free(base);
}








