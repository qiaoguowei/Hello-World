#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct stat m_stat;

    if (argc != 2)
    {
        std::cout << "usage: ftok <pathname>" << std::endl;
        return -1;
    }

    if (stat(argv[1], &m_stat) == -1)
    {
        std::cout << "stat() error. " << strerror(errno) << std::endl;
        return -1;
    }

    printf("st_dev: %lx, st_ino: %lx, key: %x\n",
            (u_long)m_stat.st_dev, (u_long)m_stat.st_ino, ftok(argv[1], 0x56));

    return 0;
}
