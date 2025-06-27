#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace  std;

int main()
{
    char buf[256];
    memset(buf, 0, sizeof(buf));
    getcwd(buf, sizeof(buf)-1);
    cout << buf << endl;
    chdir("..");
    getcwd(buf, sizeof(buf)-1);
    cout << buf << endl;
    if (access("getAppDir", F_OK) == 0)
    {
        cout << "getAppDir is exists in " << buf << endl;
    }
}
