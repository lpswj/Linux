//the version using copy per line.
#include <stdio.h>
#include <stdlib.h>
#define N 10

int main()
{
		char s[N];
		FILE *in,*out;

		in = fopen("file.in","r");
		printf("%d\n",fileno(in));
		out = fopen("file.out","w");
		printf("%d\n",fileno(out));

		while((fgets(s,N,in)) != NULL)
				fputs(s,out);

		exit(0);
}
