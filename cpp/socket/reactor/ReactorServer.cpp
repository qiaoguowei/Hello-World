#include <sys/epoll.h>
#include <vector>
#include <thread>
#include <atomic>
#include <memory>

class EventHandler
{
public:
    virtual void handleEvent(uint32_t events) = 0;
    virtual int getFd() const = 0;
};

class Reactor
{
public:
    Reactor() : epollFd_(epoll_create(0)) {}

    void registerHandler(EventHandler *handler, uint32_t events)
    {
        epoll_event ev;
        ev.events = events;
        ev.data.ptr = handler;

        epoll_ctl(epollFd_, EPOLL_CTL_ADD, handler->getFd(), &ev);
    }

    void run()
    {
        running_ = true;
        thread_ = std::thread([this](){
            constexpr int MAX_EVENTS = 64;
            epoll_event event[MAX_EVENTS];

            while (running_)
            {
                int n = epoll_wait(epollFd_, events, MAX_EVENTS, 100);
                for (int i = 0; i < n; ++i)
                {
                    auto* handler = static_cast<EventHandler*>(events[i].data.ptr);
                    handler->handleEvent(events[i].events);
                }
            }
        });
    }

    void stop()
    {
        running_ = false;
        if (thread_.joinable())
            thread_.join();

        close(epollFd_);
    }

private:
    int epollFd_;
    std::atomic<bool> running_{false};
    std::thread thread_;
};

class MainReactor
{
public:
    void start(int port)
    {
        //初始化TCP监听socket
        serverFd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        sockaddr_in addr{.sin_family = AF_INET, .sin_port = htons(port), .sin_addr{.s_addr = INADDR_ANY}};
        bind(serverFd_, (sockaddr*)&addr, sizeof(addr));
        listen(serverFd_, SOMAXCONN);
    }

private:
    Reactor mainReactor_;
    std::vector<std::unique_ptr<Reactor>> subReactor_;
    int serverFd_;
};















