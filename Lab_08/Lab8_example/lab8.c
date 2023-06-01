#include <stdio.h>
#include "apue.h"

void accumulation(int d_sum);

int main()
{
	FILE* sum;
	int total_sum=0;
	pid_t pid[5];
	int year=5, week=52, day=7;

	sum = fopen("sum.txt", "w");
	fprintf(sum, "%d\n", 0);
	fclose(sum);

	/**********************************************************/

	//Implement your code.
	TELL_WAIT();
	for(int i = 1; i <= 5; i++){
		pid[i - 1] = fork();
		if(pid[i - 1] == 0){
			for(int j = 1; j <= 52; j++){
				char filename[20];
				char id[10];
				sprintf(id, "%d", i);
				strcpy(filename, id);
				strcat(filename, "-");
				if(j < 10) strcat(filename, "0");
				sprintf(id, "%d", j);
				strcat(filename, id);
				strcat(filename, ".txt");
				FILE* fp = fopen(filename, "r");
				for(int k = 1; k <= 7; k++){
					int day_sum = 0;
					for(int l = 1; l <= 96; l++){
						int tmp;
						fscanf(fp, "%d", &tmp);
						day_sum += tmp;
					}
					WAIT_PARENT();
					accumulation(day_sum);
					TELL_PARENT(getppid());
				}
			}
			exit(0);
		}
	}
	for(int i = 0; i < 5 * 52 * 7; i++){
		TELL_CHILD(pid[i % 5]);
		WAIT_CHILD();
	}
	/**********************************************************/

	sum = fopen("sum.txt", "r");
	fscanf(sum, "%d", &total_sum);
	printf("Day_Average = %d\n",total_sum/(year*week*day));
	fclose(sum);

	return 0;
}

void accumulation(int d_sum)    //Accumulating the daily sum to "sum.txt".
{	
	FILE* sum;
	int tmp=0;

	sum = fopen("sum.txt", "r+");
	fscanf(sum, "%d", &tmp);

	tmp += d_sum;

	rewind(sum);
	fprintf(sum, "%d", tmp);
	fclose(sum);

	return;
}
