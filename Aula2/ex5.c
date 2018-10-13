#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <string.h>

int main(){
	
	pid_t r = fork();
	if (r == 0){
		printf ("Isto é o filho: pid = %d - ppid = %d\n",getpid(), getppid());
		return 0;
	}

	sleep(5);
	system("ps -f");
	printf("O pai vai terminar\n");
	return 0;

}