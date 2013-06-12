#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main()
{
		sigset_t sigset;
		sigfillset(&sigset);
		if(sigismember(&sigset,SIGINT))
				printf("SIGINT exist in signal_set!\n");
		if(sigismember(&sigset,SIGTERM))
				printf("SIGTERM exist in signal_set!\n");
		if(sigismember(&sigset,SIGABRT))
				printf("SIGABRT exist in signal_set!\n");
		if(sigdelset(&sigset,SIGINT) <0)
				perror("del error\n");
		else
				printf("SIGINT have been removed!\n");
		if(sigismember(&sigset,SIGINT))
				printf("SIGINT exist in signal_set!\n");
		else
				printf("SIGINT not exist in signal_set!\n");
		
}
