#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define	BUFFSIZE	4096

int main(void)
{
		int		n;
		char	buf[BUFFSIZE];

		int fd = open("/dev/null", O_WRONLY);  // 開啟 /dev/null，以寫入模式打開
    if (fd == -1) {
        perror("Error opening /dev/null");
        return 1;
    }
    

		while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
				if (write(fd, buf, n) != n)
						perror("write error");
				fsync(fd); // 將資料寫入硬碟

		if (n < 0)
				perror("read error");
		close(fd); // 關閉 fd，釋放資源
		exit(0);
}


