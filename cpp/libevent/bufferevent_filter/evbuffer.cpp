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
#include <event2/buffer.h>

using namespace std;

static string recvstr = "";
static int recvCount = 0;
static int sendCount = 0;

bufferevent_filter_result filter_in(evbuffer *s, evbuffer *d, ev_ssize_t limit,
        bufferevent_flush_mode mode, void *arg)
{
    cout << "filter_in" << endl;
    //读取并清理原数据
    char data[1024] = {0};
    int len = evbuffer_remove(s, data, sizeof(data)-1);

    //把所有字母转成大写
    for (int i = 0; i < len; i++)
    {
        data[i] = toupper(data[i]);
    }

    evbuffer_add(d, data, len);
    return BEV_OK;
}

bufferevent_filter_result filter_out(evbuffer *s, evbuffer *d, ev_ssize_t limit,
        bufferevent_flush_mode mode, void *arg)
{
    cout << "filter_out" << endl;
    //读取并清理原数据
    char data[1024] = {0};
    int len = evbuffer_remove(s, data, sizeof(data)-1);

    string str;
    str += "===================\n";
    str += data;
    str += "===================\n";


    evbuffer_add(d, str.c_str(), str.size());
    return BEV_OK;
}

void read_cb(bufferevent *bev, void *arg)
{
    cout << "[r]" << endl;
    char data[1024] = {};
    int len = bufferevent_read(bev, data, sizeof(data)-1);
    cout << data << endl;

    //回复客户消息, 经过输出过滤
    bufferevent_write(bev, data, len);
}

void write_cb(bufferevent *bev, void *arg)
{
    cout << "[w]" << endl;
}

void event_cb(bufferevent *bev,short events, void *arg)
{
    cout << "[event]" << endl;
}

void listen_cb(evconnlistener *ev, evutil_socket_t s, sockaddr *sin, int slen, void *arg)
{
    cout << "listen_cb" << endl;
    //创建bufferevent，
    event_base *base = (event_base *)arg;
    bufferevent *bev = bufferevent_socket_new(base, s, BEV_OPT_CLOSE_ON_FREE);
    //绑定bufferevent_filter
    bufferevent *bev_filter = bufferevent_filter_new(bev,
            filter_in, //输入过滤函数
            filter_out,//输出过滤函数
            BEV_OPT_CLOSE_ON_FREE,//关闭filter同时关闭bufferevent
            0, //清理的回调函数
            0  //传递给回调函数的参数
            );

    //设置bufferevent的回调
    bufferevent_setcb(bev_filter, read_cb, write_cb, event_cb, NULL);
    bufferevent_enable(bev_filter, EV_READ|EV_WRITE);
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








