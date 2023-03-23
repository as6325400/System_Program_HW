#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


// 0 is regular 
// 1 directory 
// 2 character 
// 3 block special 
// 4 fifo 
// 5 socket 
// 6 symbol link
int type_counts[7] = { 0 };

void traverse_directory(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;

    // 使用opendir()打開目錄
    dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // 使用readdir()讀取目錄內容
    while ((entry = readdir(dir)) != NULL) {
        char path[PATH_MAX];
        // 避免陷入無限迴圈
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(path, PATH_MAX, "%s/%s", dir_path, entry->d_name);
        // 使用lstat()取得檔案狀態
        if (lstat(path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        // 跳過符號連結，避免進入死循環
        if (S_ISLNK(statbuf.st_mode)) {
            type_counts[6]++;
            continue;
        }
        // 如果是目錄，則遞迴呼叫traverse_directory()，去遍歷該目錄
        if (S_ISDIR(statbuf.st_mode)) {
            type_counts[1]++;
            traverse_directory(path);
        } 
        else if (S_ISSOCK(statbuf.st_mode)) type_counts[5]++; // socket
        else if (S_ISREG(statbuf.st_mode)) type_counts[0]++; // regular
        else if(S_ISCHR(statbuf.st_mode)) type_counts[2]++; // character
        else if(S_ISBLK(statbuf.st_mode)) type_counts[3]++; // block special
        else if(S_ISFIFO(statbuf.st_mode)) type_counts[4]++; // fifo
        
    }

    if (closedir(dir) == -1) {
        perror("closedir");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // 從根目錄開始DFS
    traverse_directory("/");
    int total = 0;
    // 計算總數
    for(int i = 0; i < 7; i++){
        total += type_counts[i];
    }
    printf("regular: %f\n",((double)type_counts[0] / total) * 100.0);
    printf("directory: %f\n",((double)type_counts[1] / total) * 100.0);
    printf("Character special file: %f\n",((double)type_counts[2] / total) * 100.0);
    printf("Block special file: %f\n",((double)type_counts[3] / total) * 100.0);
    printf("FIFO: %f\n",((double)type_counts[4] / total) * 100.0);
    printf("Socket: %f\n",((double)type_counts[5] / total) * 100.0);
    printf("Symbolic link: %f\n",((double)type_counts[6] / total) * 100.0);
    return 0;
}