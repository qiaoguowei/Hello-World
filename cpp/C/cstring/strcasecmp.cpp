#include <iostream>
#include <cstring>
#include <signal.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

void signalFunc(int sig)
{
    cout << "receive signal is : " << sig << endl;

    exit(-1);
}

int main()
{
    struct sigaction act, oldact;
    memset(&act, 0, sizeof(act));
    act.sa_handler = signalFunc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (sigaction(SIGSEGV, &act, &oldact) < 0)
    {
        perror("sigaction");
        return -1;
    }

#if 0
    char *str = NULL;
    if (strcasecmp(str, "OK") == 0)
        cout << "true" << endl;
    cout << "end" << endl;
#else
    DIR *dp = NULL;
    struct dirent* dirp;
    dp = opendir("./ss");
    //dirp = dirent(dp);
    closedir(dp);

#endif
    sleep(5);
}


