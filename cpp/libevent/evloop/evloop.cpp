#include <iostream>
#include <string>
#include <event2/event.h>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void ctrl_c(int sock, short which, void *arg)
{
    event_base *base = (event_base *)arg;
    //event_base_loopbreak(base);

    //运行完所有的活动事件再退出，事件循环没有运行时，也要等运行一次再退出
    timeval t = {3, 0};//至少运行3秒后退出
    event_base_loopexit(base, &t);
}

int main()
{
    event_base *base = event_base_new();



    //event_base_dispatch(base);
    //EVLOOP_ONCE等待一个事件运行，直到没有活动事件退出
    //EVLOOP_NONBLOCK 有活动就处理，没有就返回0
    //EVLOOP_NO_EXIT_ON_EMPTY 没有注册事件也不返回 用于事件后期多线程添加
    event_base_loop(base, EVLOOP_ONCE);

    //event_free();
    event_base_free(base);
}








