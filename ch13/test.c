#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int file_one,file_two;
	char buffer[BUFSIZ + 1];
	int data_processed;

	memset(buffer,'\0',sizeof(buffer));

	file_one = open("/etc/passwd",O_RDONLY);
	printf("file_one's descriptor is %d\n",file_one);

	file_two = dup(file_one);
	data_processed = read(file_two,buffer,BUFSIZ);	
	if(data_processed > 0)
		printf("Read %d bytes:\n%s\n",data_processed,buffer);
//	printf("file_two's descriptor is %d\n",file_two);

}
