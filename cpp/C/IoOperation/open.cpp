#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <cstring>

using namespace std;

int main()
{
    int fd = ::open("./testFile", O_WRONLY | O_CREAT, 0664);
    if (fd < 0)
    {
        cout << "open file failed." << endl;
        return -1;
    }
    if ((write(fd, "12311\n", 6)) < 0)
    {
        cout << strerror(errno) << endl;
    }

    close(fd);
}
