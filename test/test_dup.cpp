// CPP program to illustrate dup2()  

#include <stdio.h> 
#include <fcntl.h> 
#ifdef _WIN32
#include <io.h>
#define open _open
#define dup2 _dup2
#else
#include <stdlib.h> 
#include <unistd.h> 
#endif

int main() 
{	const char* filename = "/code/github/multiprocessing/build/junk.txt";
	int fd = open(filename,O_WRONLY | O_CREAT); 
	if(-1 == fd)
	{	perror("Can't open file");
		return 1;
	}
	if(-1 == dup2(fd,_fileno(stdout)))
	{	perror("Can't dupe");
		return 2;
	}  
	printf("This will be printed in the file %s, not to console.\n",filename);   
	return 0; 
} 
