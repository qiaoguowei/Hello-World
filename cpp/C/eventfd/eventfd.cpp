#include <iostream>
#include <sys/eventfd.h>
#include <event2/event.h>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <cstring>
#include <boost/scope_exit.hpp>
#include <mutex>

using namespace std;
std::mutex mMutex;

void SendNotify(int fd)
{
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> mLock(mMutex);
        uint64_t msg = 1;
        ssize_t r;
        do
        {
            r = ::write(fd, (void *)&msg, sizeof(msg));
        }while(r < 0 && errno == EINTR);
    }
}

void printRecv(evutil_socket_t fd, short event, void *arg)
{
    event_base *base = (event_base *)arg;
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> mLock(mMutex);
        uint64_t msg;
        ssize_t r = read(fd, (void*) &msg, sizeof(msg));
        if (r > 0)
        {
            cout << "receive event massage." << endl;
        }
    }
    //event_base_loopbreak(base);
}

int main()
{
    int mEventfd = ::eventfd(0, EFD_CLOEXEC|EFD_NONBLOCK);
    if (mEventfd == -1)
    {
        strerror(errno);
        return -1;
    }

    std::thread mThread(std::bind(SendNotify, std::ref(mEventfd)));
    mThread.detach();

    event_base *base = event_base_new();

    event *mEvent = event_new(base, mEventfd, EV_READ | EV_PERSIST, printRecv, base);
    BOOST_SCOPE_EXIT(&base, &mEvent, &mEventfd)
    {
        if (mEvent != NULL)
            event_free(mEvent);
        if (base != NULL)
            event_base_free(base);
        if (mEventfd != -1)
        {
            close(mEventfd);
            mEventfd = -1;
        }
        cout << "free ......." << endl;
    }BOOST_SCOPE_EXIT_END

    event_add(mEvent, NULL);

    event_base_dispatch(base);
}














