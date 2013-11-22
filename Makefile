CC = gcc
CFLAG = -O3 -Wall

all: occupy

occupy: usemem.c
	$(CC) $(CFLAGS) -o occupy $+

clean:
	$(RM) occupy
