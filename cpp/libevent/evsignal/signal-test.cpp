#include <iostream>
#include <event2/event.h>
#include <signal.h>

/*
    #define evsignal_new(b, x, cb, arg)  event_new((b), (x), EV_SIGNAL|EV_PERSIST, (cb), (arg))
    struct event *event_new(
        struct event_base *base,
        evutil_socket_t fd,
        short events,
        void (*cb)(evutil_socket_t, short, void *),
        void *arg)
 */

int called = 0;

void signal_cb(evutil_socket_t fd, short event, void *arg)
{
    struct event *signal = static_cast<struct event *>(arg);

    std::cout << "signal_cb: got signal " << event_get_signal(signal) << std::endl;

    if (called >= 2)
        event_del(signal);

    called++;
}

int main(int argc, char *argv[])
{
    struct event *signal_int = NULL;
    struct event_base* base;
    int ret = 0;

    base = event_base_new();
    if (!base)
    {
        ret = 1;
        goto out;
    }

    signal_int = evsignal_new(base, SIGINT, signal_cb, event_self_cbarg());
    if (!signal_int)
    {
        ret = 2;
        goto out;
    }

    event_add(signal_int, NULL);

    event_base_dispatch(base);

out:
    if (signal_int)
        event_free(signal_int);
    if (base)
        event_base_free(base);
    return ret;
}










