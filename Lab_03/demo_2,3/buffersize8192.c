#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define	BUFFSIZE	8192

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

		if (n < 0)
				perror("read error");

		exit(0);
}

