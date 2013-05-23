#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

int main()
{
		int nrows,ncolumns,ncolor;
		char *result;
		char *cursor;
		char *esc_sequence;

		setupterm(NULL,fileno(stdout),(int *)0);
		nrows = tigetnum("lines");
		ncolumns = tigetnum("cols");
		ncolor = tigetnum("colors");
		result = tigetstr("acsc");
		cursor = tigetstr("cup");

		printf("This terminal has %d columns and %d rows and %d colors\n",ncolumns,nrows,ncolor);
		printf("acsc = %s\n",result);
		esc_sequence = tparm(cursor,5,30);
		putp(esc_sequence);
		exit(0);
}
