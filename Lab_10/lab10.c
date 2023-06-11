#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void put_pull_rod(int signum);
void fish_eating(int signum);
void exit_game(int signum);
void fish_eclipse();

int fishNum = 0;	// counting fish number
int boolean = 0;	// used as a boolean
int fish_eaten = 0;	// used as a boolean
int bait = 0;		// used as a boolean

struct timespec start_time, end_time;
double total_time = 0;

int main(void){
	srand(time(NULL));

	struct sigaction sig_put_pull_rod;
	sig_put_pull_rod.sa_handler = put_pull_rod;

	struct sigaction sig_exit_game;
	sig_exit_game.sa_handler = exit_game;

	struct sigaction sig_fish_eating;
	sig_fish_eating.sa_handler = fish_eating;

	//write your code here

	sigaction(SIGINT, &sig_put_pull_rod, NULL);
	sigaction(SIGTSTP, &sig_exit_game, NULL);
	sigaction(SIGALRM, &sig_fish_eating, NULL);

	printf("Fishing rod is ready!\n");
	while(1){

	}
	return 0;
}



void put_pull_rod(int signum){
	printf("\n");
	if(signum == SIGINT){
		if(boolean == 0){
			bait = 1;
			printf("Put the fishing rod\n");
			printf("Bait into water, waiting fish...\n");
			boolean = 1;
			int fish_eating_time = rand() % 3 + 1;
			alarm(fish_eating_time);
		}
		else if(boolean == 1){
			printf("Pull the fishing rod\n");
			boolean = 0;
			if(fish_eaten == 1){
				fishNum++;
				fish_eaten = 0;
				printf("Catch a Fish!!\n");
				printf("Totally caught fishes: %d\n", fishNum);
			}
			else{
				if(bait == 0) printf("The bait was eaten!!\n");
			}
			printf("Fishing rod is ready!\n");
		}
	}
}

void fish_eating(int signum){
	if(boolean == 1){
		printf("A fish is biting, pull the fishing rod\n");
		bait = 0;
		fish_eaten = 1;
		sleep(3);
		fish_eclipse();
	}
	return;
}

void fish_eclipse(){
	if(boolean == 1){
		printf("The fish was escaped\n");
		fish_eaten = 0;
	}
	
}

void exit_game(int signum){
	printf("\nTotally caught fishes: %d\n", fishNum);
	exit(0);
}

