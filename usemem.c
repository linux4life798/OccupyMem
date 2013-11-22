#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>

void writecrap(char *start, size_t size)
{
	size_t i;
	printf("- Writing %lu bytes of random crap to memory!\n", size);
	// Only consecutive from first to last
	for(i=0; i<size; i++)
		start[i] = rand();
}

int main(int argc, char *argv[])
{
	size_t size_gb = 1;
	size_t total_size = (size_gb * 1024 * 1024 * 1024);
	char *start;

	if(argc > 1) {
		if(strcmp(argv[1], "--help") == 0) {
			fprintf(stderr, "Tries to occupy some gigabytes of memory. Defaults to 1GB\n");
			fprintf(stderr, "Usage: %s [GB_of_memory_to_occupy]\n", argv[0]);
			return 1;
		}
		size_gb = (size_t)atoi(argv[1]); // should be any type problems, since number is small
		total_size = (size_gb * 1024 * 1024 * 1024);
	}

	printf("# Kindly ask for %lu GB of non-swappable memory...\n", size_gb);
	start = (char *) mmap(NULL, total_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_NORESERVE, -1, 0);
	if(start == MAP_FAILED) perror("mmap failed");

	printf("# Just to make sure the kernel is listening, we will write stuff to our entire region of memory\n");
	writecrap(start, total_size);

	printf("# Alright! I setup in vmemory space from %p to %p\n", start, start + total_size - 1);

	while(1){
		char c = 0;
		printf("Should I try to write random crap to it again(y/n)? ");
		scanf(" %c", &c);
		if(c == 'y') writecrap(start, total_size);
		else break;
	}
	munmap(start, total_size);
	return 0;
}
