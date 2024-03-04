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
    cout << data;
    if (len <= 0)
        return ;
    if (strstr(data, "quit") != NULL)
    {
        //cout << "quit" << endl;
        bufferevent_free(be);
    }
    //发送数据，写入到输出缓冲
    bufferevent_write(be, "OK", 2);
}

void write_cb(bufferevent *be, void *arg)
{
    //cout << "write" << flush;
    FILE *fp = (FILE *)arg;
    char data[1024] = {0};
    int len = fread(data, 1, sizeof(data)-1, fp);
    if (len <= 0)
    {
        fclose(fp);
        //立刻清理，可能会造成缓冲数据没有发送成功
        //bufferevent_free(be);
        bufferevent_disable(be, EV_WRITE);
        return;
    }
    //写入buffer
    bufferevent_write(be, data, len);
}

void event_cb(bufferevent *be, short events, void *arg)
{
    //cout << "event" << flush;
    //超时时间发生后，数据读取停止
    if (events & BEV_EVENT_TIMEOUT && events & BEV_EVENT_READING)
    {
        cout << "read BEV_EVENT_TIMEOUT" << endl; 
        //bufferevent_enable(be, EV_READ);
        bufferevent_free(be);
        return;
    }
    else if (events & BEV_EVENT_ERROR)
    {
        bufferevent_free(be);
        return;
    }

    if (events & BEV_EVENT_EOF)
    {
        bufferevent_free(be);
    }

    if (events & BEV_EVENT_CONNECTED)
    {
        cout << "BEV_EVENT_CONNECTED" << endl;
        //触发write
        bufferevent_trigger(be, EV_WRITE, 0);
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
            10, //低水位,0就是无限制 默认是0
            20  //高水位
            );

    bufferevent_setwatermark(bev, EV_WRITE,
            5, //低水位，缓冲区字节多于5才会发送
            0
            );

    //超时时间的设置
    timeval t1 = {3, 0};
    bufferevent_set_timeouts(bev, &t1, 0); //第二个读，第三个写


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
#if 0
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
#endif

    //调用客户端代码
    //内部创建socket -1
    bufferevent *bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9001);
    evutil_inet_pton(AF_INET, "172.22.37.100", &sin.sin_addr.s_addr);

    FILE *fp = fopen("evbuffer.cpp", "rb");

    //设置回调函数
    bufferevent_setcb(bev, read_cb, write_cb, event_cb, fp);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    int ret = bufferevent_socket_connect(bev, (sockaddr *)&sin, sizeof(sin));
    if (ret == 0)
    {
        cout << "connect" << endl;
    }

    //进入到事件的主循环
    event_base_dispatch(base);
    event_base_free(base);
}








