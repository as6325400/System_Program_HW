#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


// 定義輸入字串的大小
// 定義輸出報錯的前綴
// 定義要切割字串的分隔符號
#define BUFFER_SIZE 1024
#define ERROR "Error"
#define DELIMITER " \t\r\n\a"

int main(){

  char buffer[BUFFER_SIZE];
  char *args[100];
  int status;
  
  while (1)
  {
    printf("## ");
    fgets(buffer, BUFFER_SIZE, stdin);

    // 將字串按照設定好的分隔符切割
    int i = 0;
    args[i] = strtok(buffer, DELIMITER);
    while(args[i] != NULL){
      i++;
      args[i] = strtok(NULL, DELIMITER);
    }

    // cd是shell內置命令，不可以用execvp實現
    if(args[0] != NULL && strncmp(args[0], "cd", BUFFER_SIZE) == 0){
      // 如果cd後面沒接東西，返回環境變數"HOME"的路徑
      // 如果cd後面接的東西不存在，進行報錯
      if(args[1] != NULL){
        status = chdir(args[1]);
        if(status == -1) perror(ERROR);
      }
      else chdir(getenv("HOME"));
      continue;
    }

    // 分支一個child process，執行輸入的指令
    pid_t pid = fork();
    if(pid == 0){
      // child process
      // 若執行失敗，印出失敗原因
      if(execvp(args[0], args) == -1){
        perror(ERROR);
        exit(EXIT_FAILURE);
      }
      // 不論成功失敗，都離開child process
      exit(EXIT_SUCCESS);
    }
    else if(pid < 0){
      // pid < 0 代表fork失敗
      perror(ERROR);
    }
    else{
      // 這裡是father process
      // 等待child process裡的指令執行完
      // status的值會被改成child process的pid，跟第一個argument的pid的值是相同的
      // 第三個argument傳入0，代表等待child process結束才繼續執行
      waitpid(pid, &status, 0);
    }
  }
  return 0;
}

