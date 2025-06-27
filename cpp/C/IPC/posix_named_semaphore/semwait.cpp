#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

int main(int argc, char *argv[])
{
    sem_t *sem;
    int val = 0;
    if (argc != 2)
    {
        std::cout << "usage: semwait <name>" << std::endl;
        return -1;
    }

    sem = sem_open(argv[1], 0);
    if (sem == SEM_FAILED)
    {
        std::cout << "sem_open() failed. Error message: " << strerror(errno) << std::endl;
        return -1;
    }

    while (sem_wait(sem))
    {
        if (errno == EINTR)
            continue;
        std::cout << "sem_wait() failed. Error message: " << strerror(errno) << std::endl;
        return -1;
    }

    if (sem_getvalue(sem, &val))
    {
        std::cout << "sem_getvalue() failed. Error message: " << strerror(errno) << std::endl;
        return -1;
    }
    std::cout << "pid " << getpid() << " has semaphore, value = " << val << std::endl;

    sem_close(sem);

    return 0;
}
