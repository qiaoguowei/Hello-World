#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

/*
 * int chmod(const char *pathname, mode_t mode);
 * int fchmod(int fd, mode_t mode);
 * */

#define FILENAME "/home/qgw/my_github/Hello-World/cpp/C/FilePropertyOp/test"
#define MODE 0644

int main()
{
    const char *pathname = FILENAME;

    if (chmod(pathname, MODE) == -1)
    {
        cout << "error, change failed!" << endl;
        return -1;
    }

    cout << "OK, change successful!" << endl;
    return 0;
}
