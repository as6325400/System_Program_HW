CC = gcc
CFLAGS = -Wall -O2
TARGETS = buffersize100 buffersize4096 buffersize8192 buffersize16384

.PHONY: all clean

all: $(TARGETS)

buffersize100: buffersize100.c
	$(CC) $(CFLAGS) -o buffersize100 buffersize100.c

buffersize4096: buffersize4096.c
	$(CC) $(CFLAGS) -o buffersize4096 buffersize4096.c

buffersize8192: buffersize8192.c
	$(CC) $(CFLAGS) -o buffersize8192 buffersize8192.c

buffersize16384: buffersize16384.c
	$(CC) $(CFLAGS) -o buffersize16384 buffersize16384.c

clean:
	rm -f $(TARGETS)
