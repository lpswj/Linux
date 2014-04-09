#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
		struct stat statbuf;
		mode_t modes;

		stat("test",&statbuf);
		modes = statbuf.st_mode;

		if(S_ISREG(modes) && (modes & S_IRWXU) == S_IXUSR)
				write(1,"YES",4);
		else
				write(1,"NO",3);
		exit(0);
}
