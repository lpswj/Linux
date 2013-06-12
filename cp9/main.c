/* main.c */
#include <stdlib.h>
#include "a.h"

extern void function_two();
extern void function_three();

/*
 * This is an important file for managing this project.
 * It implements the canonical "Hello world" program.
 * Filename $RCSfile: main.c,v $
 */
static char *RCSinfo = "$Id: main.c,v 1.3 2013/06/05 01:27:42 root Exp $";

int main()
{
		function_two();
		function_three();
		printf("This file is under RCS control.Its ID is \n%s\n",RCSinfo);
		exit(EXIT_SUCCESS);
}


