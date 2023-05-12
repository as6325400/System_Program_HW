#include "apue.h"
#include <setjmp.h>
#include <string.h>

#define FILENAME "emailTest.txt"

jmp_buf	jmpbuffer;
void	do_line(char *);//start to measure email
void	compare_at(char *);//@
void	compare_sharp(char *);//#
void	compare_asterisk (char *);//*
void	compare_doubleDot(char *);//..
void	compare_dot(char *);//___@___.___

int main(void)
{
		char	line[MAXLINE];
		FILE* fp;
		fp = fopen(FILENAME,"r");
		int i;
		if((i = setjmp(jmpbuffer)) != 0){
			if (i == 1)
					printf("Email format error: at least one @ \n");
			else if(i == 2)
					printf("Email format error: more than one @ \n");
			else if(i == 3)
					printf("Email format error: cant exist # \n");
			else if(i == 4){
					printf("Email format error: cant exist * \n");
			}
			else if(i == 5){
					printf("Email format error: cant exist .. \n");
			}
			else if(i == 6){
					printf("Email format error: At least one . behind the @ \n");
			}
			//write your code here
		}
		while (fgets(line, MAXLINE, fp) != NULL)
		{	
				printf("------------------------------------------------\n");
				printf("%s",line);
				do_line(line);		
		}
		exit(0);
}
void do_line(char *str)		/* process one line of input */
{
		compare_at(str);
		printf ("valid email address!\n");
		return;
}	

void compare_at(char *str)
{
		int counter = 0;
		char* 	cptr;
		char*	temp;	
		if((cptr = strchr(str,'@')) == NULL) 
				longjmp(jmpbuffer, 1);  //at least one @	
		temp = cptr;
		while((cptr = strchr(temp,'@')) != NULL)
		{							
				printf ("@ found at %ld\n",cptr-str+1);				
				counter++;
				temp = cptr+1;			
		}
		if(counter > 1)
				longjmp(jmpbuffer, 2);	//more than one @	
		compare_sharp(str);
		return;
}

void compare_sharp(char *str)
{		
		int counter = 0;
		char* 	cptr;
		char*	temp;	
		if((cptr = strchr(str,'#')) == NULL){} 
		else{
				temp = cptr;
				while((cptr = strchr(temp,'#')) != NULL)
				{							
						printf ("# found at %ld\n",cptr-str+1);				
						counter++;
						temp = cptr+1;			
				}
				if(counter > 0)
						longjmp(jmpbuffer, 3);	//cant exist #
		}
		compare_asterisk(str);
		return;
}

void compare_asterisk(char *str)
{		
		int counter = 0;
		char* 	cptr;
		char*	temp;	
		if((cptr = strchr(str,'*')) == NULL){} 
		else{
				temp = cptr;
				while((cptr = strchr(temp,'*')) != NULL)
				{							
						printf ("* found at %ld\n",cptr-str+1);				
						counter++;
						temp = cptr+1;			
				}
				if(counter > 0)
						longjmp(jmpbuffer, 4);	//cant exist #
		}
		compare_doubleDot(str);	
		return;
}

void compare_doubleDot(char *str)
{	
		int counter = 0;
		char* 	cptr;
		char*	temp;	
		if((cptr = strstr(str,"..")) == NULL){} 
		else{
				temp = cptr;
				while((cptr = strstr(temp,"..")) != NULL)
				{							
						printf (".. found at %ld\n",cptr-str+1);				
						counter++;
						temp = cptr+1;			
				}
				if(counter > 0)
						longjmp(jmpbuffer, 5);	//cant exist ..
		}
		compare_dot(str);
		return;
}

void compare_dot(char *str)
{		
		int counter = 0;
		char* 	cptr;
		char*	temp;	
		if((cptr = strchr(str,'.')) == NULL){
				longjmp(jmpbuffer, 6);	
		} 
		else{
				temp = str;
				int index = 0, index2 = 0;
				while((cptr = strchr(temp,'@')) != NULL)
				{		
						index = cptr-str+1;	
						counter++;
						temp = cptr+1;			
				}
				temp = str;
				while((cptr = strchr(temp,'.')) != NULL)
				{							
						index2 = cptr-str+1;
						temp = cptr+1;			
				}
				if(index2 <= index){
						longjmp(jmpbuffer, 6);	
				}
		}
		return;
}
