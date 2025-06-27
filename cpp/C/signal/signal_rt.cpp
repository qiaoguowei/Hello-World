#include <iostream>
#include <signal.h>

typedef void Sigfunc_rt(int, siginfo_t *, void *);

Sigfunc_rt *signal_rt(int signo, Sigfunc_rt *func, sigset_t *mask)
{
    struct sigaction act, oact;

    act.sa_sigaction = func;
    act.sa_mask = *mask;
    act.sa_flag = SA_SIGINFO;
    if (signo == SIGALRM)
    {
#ifdef SA_INTERRUPT
        act.flag |= SA_INTERRUPT;
#endif
    }
    else
    {
#ifdef SA_RESTART
        act.flag |= SA_RESTART;
#endif
    }
    if (sigaction(signo, &act, &oact) < 0)
    {
        std::cout << "sigaction() failed. error: " << strerror(errno) << std::endl;
        return nullptr;
    }

    return oact.sa_sigaction;
}
