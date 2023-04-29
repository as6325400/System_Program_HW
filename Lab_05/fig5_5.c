#include "apue.h"

int main(void)
{
	char buf[MAXLINE];
	long long counter = 0;

	setvbuf(stdin,NULL,_IONBF,0);
	setvbuf(stdout,NULL,_IONBF,0);

	while( (fgets(buf,MAXLINE,stdin)) != NULL ){
		if(counter % 100 == 0) printf("counter = %lld\n",counter);
		counter++;
		if(fputs(buf,stdout) == EOF)
			err_sys("output error");
	}
	if(ferror(stdin))
		err_sys("input error");

	printf("counter = %lld\n",counter);
	exit(0);
}

