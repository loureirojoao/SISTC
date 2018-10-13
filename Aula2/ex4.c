#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <string.h>

int main()
{
	pid_t r = fork();
	
	

	if (r > 0) {
		sleep(1);
		exit(0);
		
	}
	
	printf("pid = %d - ppid = %d\n",getpid(), getppid());
	sleep(2);

	printf("pid = %d - ppid = %d\n",getpid(), getppid());

	return(0);

}