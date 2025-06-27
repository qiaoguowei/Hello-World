#include <iostream>
#include <sys/timerfd.h>
#include <string>
#include <cstring>
#include <sys/epoll.h>
#include <unistd.h>

#define MAX_EVENTS 10
using namespace std;

int main()
{
    int mTimerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK|TFD_CLOEXEC);
    if (mTimerfd == -1)
    {
        cout << strerror(errno) << endl;
        return -1;
    }

    struct epoll_event ev, events[MAX_EVENTS];
    int epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        cout << strerror(errno) << endl;
        return -1;
    }

    ev.events = EPOLLIN;
    ev.data.fd = mTimerfd;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, mTimerfd, &ev) == -1)
    {
        cout << strerror(errno) << endl;
        return -1;
    }

    struct itimerspec new_timer = {0};
    new_timer.it_value.tv_sec = 3;
    new_timer.it_value.tv_nsec = 0;
    new_timer.it_interval.tv_sec = 3;
    new_timer.it_interval.tv_nsec = 0;
    if (timerfd_settime(mTimerfd, 0, &new_timer, NULL) == -1)
    {
        cout << strerror(errno) << endl;
        return -1;
    }

    char buf[1024];
    while (1)
    {
        int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            return -1;
        }
        for (int i = 0; i < nfds; i++)
        {
            if (events[i].data.fd == mTimerfd)
            {
                memset(buf, 0, sizeof(buf));
                int readNum = ::read(mTimerfd, buf, sizeof(buf)-1);
                if (readNum < 0)
                {
                    if (errno != EINTR)
                    {
                        cout << strerror(errno) << endl;
                        break;
                    }
                    continue;
                }
                else if(readNum == 0)
                {
                    cout << "read end of the cache." << endl;
                    break;
                }
                else
                {
                    cout << buf << endl;
<<<<<<< HEAD
                    cout << "11111" << std::endl;
=======
>>>>>>> 4adb3f20a968faa466b0157e6da162535c178879
                }
                cout << "timeout......" << endl;
            }
        }
    }

    return 0;
}
