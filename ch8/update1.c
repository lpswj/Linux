#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

int main(int argc,char *argv[])
{
		MYSQL my_connection;
		int res;

		mysql_init(&my_connection);
		if(mysql_real_connect(&my_connection,"localhost","rick","secret","foo",0,NULL,CLIENT_FOUND_ROWS)){
				printf("Connect success\n");
				res = mysql_query(&my_connection,"UPDATE children SET AGE = 99 WHERE fname = 'Ann'");
				if(!res){
						printf("Inserted %lu rows\n",(unsigned long)mysql_affected_rows(&my_connection));
				}else{
						fprintf(stderr,"Insert error %d:%s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
				}

				mysql_close(&my_connection);
		}else{
				fprintf(stderr,"Connection failed\n");
				if(mysql_errno(&my_connection)){
						fprintf(stderr,"Connection error %d:%s\n",
										mysql_errno(&my_connection),mysql_error(&my_connection));
				}
		}
		return EXIT_SUCCESS;

}
