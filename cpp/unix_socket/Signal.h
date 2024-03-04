#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <iostream>
#include <signal.h>

void children_exit_signal_handler(int signum)
{
	pid_t mpid;
	int status;

	while ((mpid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		
	}
}

typedef void (*signal_handler)(int)

int Signal(int signum, signal_handler m_handler)
{
	struct sigaction act, oldact;

	act.sa_handler = m_handler;
	sigemptyset(&act.sa_mask);
	if (signum == )
}


#endif


