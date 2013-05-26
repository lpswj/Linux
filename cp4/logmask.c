#include <syslog.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
		int logmask;

		openlog("logmask",LOG_PID|LOG_CONS,LOG_USER);
		syslog(LOG_EMERG,"informative message,pid = %d",getpid());
		syslog(LOG_DEBUG,"debug message,should appear");
		//priority below the LOG_NOTICE will not appear
		logmask = setlogmask(LOG_UPTO(LOG_NOTICE));
		syslog(LOG_DEBUG,"debug message,should not appear");
		exit(0);
}