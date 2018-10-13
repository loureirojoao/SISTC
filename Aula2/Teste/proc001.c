
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

int main(void)

{
	printf("hello world from process ID %ld\n", (long)getpid());
	exit(0);
}