#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

void msg(int signo)
{
		if(signo == SIGINT)
				printf("Get SIGINT!\n");
		else
				printf("Get SIGQUIT!\n");
}

int main()
{
		sigset_t sigset,oset;
		sigemptyset(&sigset);
		sigaddset(&sigset,SIGINT);
		sigprocmask(SIG_BLOCK,&sigset,&oset);
		signal(SIGINT,msg);
		signal(SIGQUIT,msg);
		sleep(2);
		raise(SIGINT);
		raise(SIGQUIT);

}

