#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void client(int, int);
void server(int, int);

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"

int main(int argc, char *argv[])
{
    int readfd, writefd;
    pid_t child_pid;

    if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))
    {
        std::cout << "can't create " << FIFO1 << ". error: " << strerror(errno) << std::endl;
        return -1;
    }
    if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST))
    {
        unlink(FIFO1);
        std::cout << "can't create " << FIFO2 << ". error: " << strerror(errno) << std::endl;
        return -1;
    }

    child_pid = fork();
    if (child_pid < 0)
    {
        std::cout << "fork() failed. error: " << strerror(errno) << std::endl;
        unlink(FIFO1);
        unlink(FIFO2);
        return -1;
    }
    else if (child_pid == 0)
    {
        readfd = open(FIFO1, O_RDONLY, 0);
        if (readfd < 0)
        {
            std::cout << "open() failed. error: " << strerror(errno) << std::endl;
            exit(0);
        }
        writefd = open(FIFO2, O_WRONLY, 0);
        if (writefd < 0)
        {
            std::cout << "open() failed. error: " << strerror(errno) << std::endl;
            exit(0);
        }
        server(readfd, writefd);
        exit(0);
    }

    writefd = open(FIFO1, O_WRONLY, 0);
    if (writefd < 0)
    {
        std::cout << "open() failed. error: " << strerror(errno) << std::endl;
        waitpid(child_pid, NULL, 0);
        unlink(FIFO1);
        unlink(FIFO2);
        exit(0);
    }
    readfd = open(FIFO2, O_RDONLY, 0);
    if (readfd < 0)
    {
        std::cout << "open() failed. error: " << strerror(errno) << std::endl;
        close(writefd);
        waitpid(child_pid, NULL, 0);
        unlink(FIFO1);
        unlink(FIFO2);
        exit(0);
    }

    client(readfd, writefd);

    waitpid(child_pid, NULL, 0);

    close(writefd);
    close(readfd);

    unlink(FIFO1);
    unlink(FIFO2);
    exit(0);
}

void client(int readfd, int writefd)
{
    size_t len;
    ssize_t n;
    char buff[1024];

    memset(buff, 0, sizeof(buff));
    ::fgets(buff, sizeof(buff) - 1, stdin);
    len = ::strlen(buff);
    if (buff[len-1] == '\n')
        len--;

    ::write(writefd, buff, len);

    memset(buff, 0, sizeof(buff));
    while ( (n = ::read(readfd, buff, sizeof(buff) - 1)) > 0)
    {
        ::write(STDOUT_FILENO, buff, n);
    }
}

void server(int readfd, int writefd)
{
    int fd;
    ssize_t n;
    char buff[1024];

    if ( (n = read(readfd, buff, sizeof(buff) - 1)) == 0)
    {
        std::cout << "end-of-file while reading pathname" << std::endl;
        return;
    }
    buff[n] = '\0';

    if ( (fd = open(buff, O_RDONLY)) < 0)
    {
        std::cout << "read file failed. error: " << strerror(errno) << ", filename: " << buff << std::endl;
        n = strlen(buff);
        write(writefd, buff, n);
    }
    else
    {
        while ( (n = read(fd, buff, sizeof(buff))) > 0)
        {
            write(writefd, buff, n);
        }
        close(fd);
    }
}

