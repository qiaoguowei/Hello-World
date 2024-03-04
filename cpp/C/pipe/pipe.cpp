#include <iostream>
#include <functional>
#include <thread>
#include <unistd.h>
#include <event2/event.h>
#include <string>
#include <cstring>
#include <chrono>
#include <fcntl.h> 

using namespace std;

void PipeWrite(int fd)
{
    if (fd < 0)
    {
        cout << "the fd is invalid." << endl;
        return ;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::string writeBuf = "send some to fd[0].";
    if (::write(fd, writeBuf.c_str(), writeBuf.size()) < 0)
    {
        cout << strerror(errno) << endl;
        return ;
    }
}

void PipeRecv(evutil_socket_t fd, short event, void *arg)
{
    event_base *base = (event_base *)arg;
    if (fd < 0)
    {
        event_base_loopbreak(base);
        return ;
    }

    ssize_t r = 0;
    char buf[1024];
    do {
        ::memset(buf, 0, sizeof(buf));
        r = ::read(fd, buf, sizeof(buf)-1);
    } while(r < 0 && errno == EINTR);
    cout << buf << endl;

    event_base_loopbreak(base);
}

int main()
{
    int pipefd[2] = {0};
    if (pipe2(pipefd, O_CLOEXEC|O_NONBLOCK) == -1)
    {
        cout << strerror(errno) << endl;
        return -1;
    }

    std::thread mThread(std::bind(PipeWrite, std::ref(pipefd[1])));

    event_base *base = event_base_new();
    if (base == NULL)
    {
        //goto err1;
        close(pipefd[0]);
        close(pipefd[1]);
        mThread.join();
        return -1;
    }
    event *mEvent = event_new(base, pipefd[0], EV_READ | EV_PERSIST, PipeRecv, base);
    if (mEvent == NULL)
    {
        goto err2;
    }
    event_add(mEvent, NULL);
    event_base_dispatch(base);

    event_free(mEvent);

err2:
    event_base_free(base);
    close(pipefd[0]);
    close(pipefd[1]);
    mThread.join();

    return 0;
}

















