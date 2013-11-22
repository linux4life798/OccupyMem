CC = gcc
W64CC = x86_64-w64-mingw32-gcc
W32CC = i686-w64-mingw32-gcc
CFLAGS = -O3 -Wall

.PHONY: all clean

all: occupy occupy-w64.exe occupy-w32.exe

occupy: usemem.c
	$(CC) $(CFLAGS) -o $@ $+

occupy-w64.exe: usemem.c
	$(W64CC) $(CFLAGS) -o $@ $+

occupy-w32.exe: usemem.c
	$(W32CC) $(CFLAGS) -o $@ $+

clean:
	$(RM) *.o occupy *.exe
