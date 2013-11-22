A C program that simply reserves a specified large amount of memory.

* For the cases when the kernel wants to delay allocating physical memory, the program will iteratively write to each address in an attempt to occupy it.
* The program uses malloc for widows and mmap for non-windows compilations.


When invoked without arguments, it will reserve 1 GB by default.


For POSIX and GNU environments:
	Usage: occupy [size_in_GB]

For Windows 32-bit:
	Usage: occupy-w32 [size_in_GB]

For Windows 64-bit:
	Usage: occupy-w64 [size_in_GB]
