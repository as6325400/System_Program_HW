#include "apue.h"

int main(void)
{

	int c;
	long long counter = 0;
	while( (c = getc(stdin)) != EOF ){
		counter++;
		if(putc(c,stdout) == EOF)
			err_sys("output error");
	}
		
	if(ferror(stdin))
		err_sys("input error");
	printf("counter = %lld\n",counter);
	exit(0);
}

