#include <iostream>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[])
{
    mqd_t mqd;
    char *ptr;
    size_t len;
    unsigned int prio;
    struct mq_attr attr;

    if (argc != 4)
    {
        std::cout << "usage: mqsend <name> <bytes> <priority>" << std::endl;
        return -1;
    }
    len = atoi(argv[2]);
    prio = atoi(argv[3]);
    attr.mq_maxmsg = 8;
    attr.mq_msgsize = 1024;
#if 0
    if ( (mqd = mq_open("/home/qgw/my_github/Hello-World/cpp/C/IPC/mqueue/xxx", O_RDWR | O_CREAT, 0644, NULL)) == -1)
#endif
    if ( (mqd = mq_open("/mqueue.1", O_RDWR | O_CREAT, 0644, NULL)) == -1)
    {
        std::cout << "mq_open failed. explan: " << strerror(errno) << std::endl;
        return -1;
    }

    ptr = (char *)calloc(len, sizeof(char));
    if (!ptr)
    {
        std::cout << "calloc failed. " << std::endl;
        return -1;
    }

    snprintf(ptr, len, "mqsend infomation, priority is %u.", prio);
    if (mq_send(mqd, ptr, len, prio) == -1)
    {
        std::cout << "mq_send failed. explan: " << strerror(errno) << std::endl;
        free(ptr);
        return -1;
    }
    std::cout << "mq_send() success." << std::endl;
    free(ptr);

    return 0;
}
