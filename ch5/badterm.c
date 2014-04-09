#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

int main()
{
		setupterm("unlisted",fileno(stdout),(int *)0);
		printf("Done.\n");
		exit(0);
}
