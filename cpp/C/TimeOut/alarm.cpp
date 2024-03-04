#include <iostream>

typedef sighandler_t Sigfunc;

static void connect_alarm(int);

int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nsec)
{
    Sigfunc *sigfunc;
    int n;

    sigfunc = Signal(SIGALRM, connnect_alarm);
    if (alarm(nsec) != 0)
    {
        cerr << "connect_timeo: alarm was already set" << endl;
    }

    if ((n = connect(sockfd, saptr, salen)) < 0)
    {
        close(sockfd);
        if (errno == EINTR)
            errno = ETIMEDOUT;
    }
    alarm(0);                   //turn off the alarm
    Signal(SIGALRM, sigfunc);   //restore previous signal handler

    return n;
}

static void connect_alarm(int signo)
{
    return;     //just interrupt the connect()
}



