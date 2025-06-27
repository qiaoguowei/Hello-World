#include <iostream>
#include <string>
#include <event2/event.h>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

/*
    #define evutil_socket_t int
 */
void readfile(evutil_socket_t fd, short event, void *arg)
{
    char buf[1024] = {0};
    int len = read(fd, buf, sizeof(buf)-1);
    if (len > 0)
    {
        cout << buf << endl;
        cout << "readfile" << endl;
        cout << this_thread::get_id() << endl;
    }
    else
    {

    }
}

int main()
{
    cout << this_thread::get_id() << endl;
    event_config *conf = event_config_new();
    //设置支持文件描述符
    event_config_require_features(conf, EV_FEATURE_FDS);
    struct event_base *base = event_base_new_with_config(conf);
    event_config_free(conf);
    cout << event_base_get_method(base) << endl;

    if (!base)
    {
        cout << "event base failed" << endl;
        return -1;
    }

    int sock = open("/var/log/auth.log", O_RDONLY | O_NONBLOCK, 0);
    if (sock < 0)
    {
        cout << "open file failed." << endl;
        event_base_free(base);
        return -1;
    }
    //文件指针移到结尾处
    lseek(sock, 0, SEEK_END);
    //监听文件数据
    event *fev = event_new(base, sock, EV_READ | EV_PERSIST, readfile, 0);
    event_add(fev, NULL);


    cout << "test file" << endl;


    event_base_dispatch(base);
    event_free(fev);
    event_base_free(base);
}








