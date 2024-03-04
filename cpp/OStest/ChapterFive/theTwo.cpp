#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    int fd = ::open("./testFile", O_CREAT | O_WRONLY, 0644);
    if (fd == -1)
    {
        cout << "open file failed." << endl;
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        cout << "call fork() failed." << endl;
        return -1;
    }
    else if (pid == 0)
    {
        for (int i = 0; i < 100; i++)
        {
            int ret = write(fd, "aaaaaaaaaa\n", 11);
            if (ret <= 0)
            {
                cout << "write to file failed." << endl;
                exit(1);
            }
        }
        close(fd);
        exit(0);
    }

    for (int i = 0; i < 100; i++)
    {
        int ret = write(fd, "bbbbbbbbbb", 10);
        if (ret <= 0)
        {
            cout << "[parent] write to file failed." << endl;
            wait(NULL);
        }
    }

    close(fd);
    wait(NULL);
}
