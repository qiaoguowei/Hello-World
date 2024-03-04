#include <iostream>
#include <string>
#include <event2/event.h>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <event2/listener.h>
#include <event2/bufferevent.h>

using namespace std;

static string recvstr = "";
static int recvCount = 0;
static int sendCount = 0;

void read_cb(bufferevent *be, void *arg)
{
    //cout << "read" << flush;
    char data[1024] = {0};
    //读取缓冲数据
    int len = bufferevent_read(be, data, sizeof(data)-1);
    cout << data << flush;
    if (len <= 0) return ;
    if (strstr(data, "quit") != NULL)
    {
        cout << "quit" << endl;
        bufferevent_free(be);
    }
    //发送数据，写入到输出缓冲
    //bufferevent_write(be, "OK", 2);
}

void write_cb(bufferevent *be, void *arg)
{
    //cout << "write" << flush;
}

void event_cb(bufferevent *be, short events, void *arg)
{
    cout << "event" << flush;
    //超时时间发生后，数据读取停止
    if (events & BEV_EVENT_TIMEOUT && events & BEV_EVENT_READING)
    {
        char data[1024] = {0};
        //读取缓冲数据
        int len = bufferevent_read(be, data, sizeof(data)-1);
        if (len > 0)
            cout << data << flush;

        cout << "read BEV_EVENT_TIMEOUT" << endl; 
        //bufferevent_enable(be, EV_READ);
        bufferevent_free(be);
    }
    else if (events & BEV_EVENT_ERROR)
    {
        bufferevent_free(be);
    }
    else
    {
        cout << "OTHERS" << endl;
    }
}

void listen_cb(evconnlistener *ev, evutil_socket_t s, sockaddr *sin, int slen, void *arg)
{
    cout << "listen_cb" << endl;
    event_base *base = (event_base *)arg;

    //BEV_OPT_CLOSE_ON_FREE清理bufferevent时关闭socket
    bufferevent *bev = bufferevent_socket_new(base, s, BEV_OPT_CLOSE_ON_FREE);
    //添加监控事件
    bufferevent_enable(bev, EV_READ|EV_WRITE);

    //设置水位
    //读取水位
    bufferevent_setwatermark(bev, EV_READ,
            0,  //低水位,0就是无限制 默认是0
            0   //高水位
            );

    bufferevent_setwatermark(bev, EV_WRITE,
            0, //低水位，缓冲区字节多于5才会发送
            0
            );

    //超时时间的设置
    timeval t1 = {3, 0};
    //bufferevent_set_timeouts(bev, &t1, 0); //第二个读，第三个写


    //设置回调函数
    bufferevent_setcb(bev, read_cb, write_cb, event_cb, base);
}


int main()
{
    struct event_base *base = event_base_new();

    if (!base)
    {
        cout << "event base failed" << endl;
        return -1;
    }

    //创建网络服务器
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9001);

    evconnlistener *ev = evconnlistener_new_bind(base,
                                                 listen_cb,
                                                 base,
                                                 LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
                                                 10, //监听个数
                                                 (sockaddr *)&sin,
                                                 sizeof(sin));



    //进入到事件的主循环
    event_base_dispatch(base);
    evconnlistener_free(ev);
    event_base_free(base);
}








