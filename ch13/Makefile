PIPE=popen1 popen2 popen3 popen4 pipe1 pipe2 pipe3 pipe4 pipe5 fifo1 fifo2 fifo3 fifo4 client server

all:$(PIPE)

$(PIPE):
	$(CC) $(CFLAGS) $@.c -o $@ 

CC=gcc
CFLAGS=-ggdb -std=gnu99 -Wall -Werror -Wformat=0

clean:
	rm -f $(PIPE) a.out *.o core


