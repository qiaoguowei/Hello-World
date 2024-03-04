#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char *argv[])
{
    int     c, flags;
    sem_t   *sem;
    unsigned int value;

    flags = O_RDWR | O_CREAT;
    value = 1;

    while ( (c = getopt(argc, argv, "ei:")) != -1)
    {
        switch (c)
        {
            case 'e':
                flags |= O_EXCL;
                break;
            case 'i':
                value  = atoi(optarg);
                break;
        }
    }

    if (optind != argc - 1)
    {
        std::cout << "usage: semcreate [-e] [-i initalvalue] <name>" << std::endl;
        return -1;
    }

    sem = sem_open(argv[optind], flags, FILE_MODE, value);
    if (sem == SEM_FAILED)
    {
        std::cout << "sem_open() failed. Error message: " << strerror(errno) << std::endl;
        return -1;
    }

    sem_close(sem);
    return 0;
}
