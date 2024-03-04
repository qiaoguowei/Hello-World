#include <iostream>
#include <string>
#include <event2/event.h>
#include <thread>

using namespace std;
static timeval t1 = {1, 0};

void timer1(int sock, short which, void *arg)
{
    cout << "timer1" << endl;
    //no pending
    event *ev = (event *)arg;
    cout << this_thread::get_id() << endl;
    if (!evtimer_pending(ev, &t1))
    {
        evtimer_del(ev);
        evtimer_add(ev, &t1);
    }
}

void timer2(int sock, short which, void *arg)
{
    cout << "timer2" << endl;
    cout << this_thread::get_id() << endl;
}

void timer3(int sock, short which, void *arg)
{
    cout << "timer3" << endl;
    //this_thread::sleep_for(3000ms);
    cout << this_thread::get_id() << endl;
}

int main()
{
    struct event_base *base = event_base_new();

    //定时器
    cout << "test timer" << endl;
    cout << this_thread::get_id() << endl;

    //event_new
    //#define evtimer_new(b, cb, arg)   event_new((b), -1, 0, (cb), (arg))
    //#define evtimer_add(ev, tv)       event_add((ev), (tv))
    //#define evtimer_del(ev)           event_del((ev))
    //定时器非持久状态
    event *ev1 = evtimer_new(base, timer1, event_self_cbarg());
    if (!ev1)
    {
        cout << "evtimer_new timer1 failed!" << endl;
        return -1;
    }
    evtimer_add(ev1, &t1);

    static timeval t2;
    t2.tv_sec = 1;
    t2.tv_usec = 200000;
    event *ev2 = event_new(base, -1, EV_PERSIST, timer2, 0);
    event_add(ev2, &t2);

    //超时优化性能优化，默认event用二叉堆存储(完全二叉树) O(logn)
    //优化到双向队列 O(1)
    //
    event *ev3 = event_new(base, -1, EV_PERSIST, timer3, 0);

    static timeval tv_in = {3, 0};
    const timeval *t3;
    t3 = event_base_init_common_timeout(base, &tv_in);
    event_add(ev3, t3); //插入性能 O(1);之前的是O(logn)


    event_base_dispatch(base);
    event_free(ev1);
    event_free(ev2);
    event_free(ev3);
    event_base_free(base);
}








