/** Very quick program to reserve large portitons of memory
 *   -More for the concept
 * @author Craig Hesling
 * @date 11/22/2013
 */

#if defined __MINGW32__
	#define METHOD_MALLOC
#else
	#define METHOD_MMAP
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef METHOD_MMAP
	#include <sys/mman.h>
#endif

/* Windows doesn't have mmap - use malloc */
//#define METHOD_MMAP
//#define METHOD_MALLOC

/* Reserve 'size' Bytes of memory - return start address */
char *reservememory(size_t size)
{
	char *start = NULL; //= MAP_FAILED;
	printf("# Kindly ask for %.2lf GB of memory\n", ((double)size)/(1024*1024*1024) );
	
#if defined (METHOD_MMAP)
	start = (char *) mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_NORESERVE, -1, 0);
	if(start == MAP_FAILED) perror("mmap failed");
#elif defined (METHOD_MALLOC)
	start = (char *) malloc(size);
	if(start == NULL) perror("malloc failed");
#else
	#error
#endif

	return start;
}

/* Clean up the reserved memory */
void returnmemory(char *start, size_t size)
{

#if defined (METHOD_MMAP)
	munmap(start, size);
#elif defined (METHOD_MALLOC)
	free(start);
#else
	#error
#endif

}

/* Write random values to the 'size' elements in the array starting at 'start' */
void writestuff(char *start, size_t size)
{
	size_t i;
	printf("# Writing %lu bytes of random crap to memory!\n", (long unsigned int)size);
	// Only consecutive from first to last
	for(i=0; i<size; i++)
		start[i] = rand();
}




/* first argument(optional) specifies size in GB to reserve */
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

	start = reservememory(total_size);

	printf("# Just to make sure the kernel is listening, we will write stuff to our entire region of memory\n");
	writestuff(start, total_size);

	printf("# Alright! I setup in vmemory space from %p to %p\n", start, start + total_size - 1);

	while(1){
		char c = 0;
		printf("Should I try to write random stuff to it again(y/n)? ");
		scanf(" %c", &c);
		if(c == 'y') writestuff(start, total_size);
		else break;
	}
	returnmemory(start, total_size);
	return 0;
}
