#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void client(int, int);
void server(int, int);

int main(int argc, char *argv[])
{
    int pipe1[2];
    int pipe2[2];
    pid_t child_pid;

    if (::pipe(pipe1))
    {
        std::cout << "pipe() error. " << strerror(errno) << std::endl;
        return -1;
    }
    if (::pipe(pipe2))
    {
        std::cout << "pipe() error. " << strerror(errno) << std::endl;
        return -1;
    }

    child_pid = ::fork();
    if (child_pid < 0)
    {
        std::cout << "fork() error. " << strerror(errno) << std::endl;
        return -1;
    }
    else if (child_pid == 0)
    {
        ::close(pipe1[1]);
        ::close(pipe2[0]);

        server(pipe1[0], pipe2[1]);
        ::exit(0);
    }

    ::close(pipe1[0]);
    ::close(pipe2[1]);
    client(pipe2[0], pipe1[1]);

    ::waitpid(child_pid, NULL, 0);
    ::exit(0);
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

