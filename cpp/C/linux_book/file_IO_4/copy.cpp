#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


using namespace std;

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE] = {0};

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
    {
        cout << argv[0] << " old-file new-file" << endl;
        return -1;
    }

    /*open input and output files */
    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
    {
        cout << "open file " << argv[1] << " failed. message: " << strerror(errno) << endl;
        return -1;
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
    {
        cout << "open file " << argv[2] << " failed. message: " << strerror(errno) << endl;
        return -1;
    }

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
    {
        char * p = buf;
        while (1)
        {
            int writeNum = write(outputFd, p, numRead);
            if (writeNum == -1)
            {
                cout << "write(): " << strerror(errno) << endl;
                return -1;
            }
            numRead -= writeNum;
            if (numRead == 0)
                break;
            p += writeNum;
        }
        memset(buf, 0, sizeof(buf));
    }

    if (numRead == -1)
    {
        cout << "read(): " << strerror(errno) << endl;
        return -1;
    }

    if (close(inputFd) == -1)
    {
        perror("close()");
        return -1;
    }
    if (close(outputFd) == -1)
    {
        perror("close()");
        return -1;
    }

    return -1;
}
















