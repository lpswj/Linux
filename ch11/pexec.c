#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
		int res;

		printf("Running ps with execlp\n");
		res = execlp("ps","ps","ax",(char *)0);
		if(res == -1)
				fprintf(stderr,"execlp failed\n");
		printf("Done.\n");
		exit(0);
}
