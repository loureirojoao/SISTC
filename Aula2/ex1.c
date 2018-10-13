#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

int i = 0;

int main() {
	
	pid_t r = fork();
	if (r == 0) {
		sleep(10);
		printf ("%d: %d %d \n", getpid(), i, r );
		//return 0 ;
	}

	i = + 1;
	wait(NULL);
	printf ("%d: %d %d \n", getpid(), i, r );
	return 0;
}
