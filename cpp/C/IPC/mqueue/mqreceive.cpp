#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>

const char *mq_name = "/mqueue.1";

int main(int argc, char *argv[])
{
    int         c, flags;
    mqd_t       mqd;
    ssize_t     n;
    uint32_t    prio;
    char        *buff;
    struct mq_attr attr;

    flags = O_RDONLY;
    if ( (mqd = mq_open(mq_name, flags)) == -1)
    {
        std::cout << "mq_open failed. explan: " << strerror(errno) << std::endl;
        return -1;
    }

    if (mq_getattr(mqd, &attr))
    {
        std::cout << "mq_getattr failed. explan: " << strerror(errno) << std::endl;
        mq_close(mqd);
        return -1;
    }

    buff = (char *)malloc(attr.mq_msgsize);
    if ( (n = mq_receive(mqd, buff, attr.mq_msgsize, &prio)) == -1)
    {
        std::cout << "mq_receive failed. explan: " << strerror(errno) << std::endl;
        free(buff);
        mq_close(mqd);
        return -1;
    }
    std::cout << "mq_receive: " << buff << std::endl;
    free(buff);
    mq_close(mqd);
    return 0;
}
