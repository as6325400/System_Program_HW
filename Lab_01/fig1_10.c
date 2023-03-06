#include "apue.h"
#include <sys/wait.h>

#define DELIMITER " \t\r\n\a"
#define ERROR "Error"

static void sig_int(int); /* our signal-catching function */
int main(void)
{
	char buf[MAXLINE]; /* from apue.h */
	char *args[100];
	pid_t pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	printf("## "); /* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		// 將字串按照設定好的分隔符切割
		int i = 0;
		args[i] = strtok(buf, DELIMITER);
		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, DELIMITER);
		}

		// cd是shell內置命令，不可以用execvp實現
		if (args[0] != NULL && strncmp(args[0], "cd", MAXLINE) == 0)
		{
			// 如果cd後面沒接東西，返回環境變數"HOME"的路徑
			// 如果cd後面接的東西不存在，進行報錯
			if (args[1] != NULL)
			{	
				status = chdir(args[1]);
				if (status == -1) perror(ERROR);
			}
			else chdir(getenv("HOME"));
		}
		else
		{
			pid_t pid = fork();

			if (pid < 0)
			{
				err_sys("fork error");
			}
			else if (pid == 0)
			{ /* child */
				execvp(args[0], args);
				err_ret("couldn't execute: %s", buf);
				exit(127);
			}
			/* parent */
			if ((pid = waitpid(pid, &status, 0)) < 0)
				err_sys("waitpid error");	
		}
		printf("## ");
	}
	exit(0);
}

void sig_int(int signo)
{
	printf("interrupt\n%% ");
}
