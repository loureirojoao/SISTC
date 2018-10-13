//Ex iii

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void myhandler(int signum);

int main(){

	sigset_t sigset;
	struct sigaction act;

	sigemptyset(&sigset); // Começar com a máscara vazia
	sigaddset(&sigset, SIGINT); // Acrescentar SIGINT 
	sigaddset(&sigset, SIGQUIT); // Acrescentar SIGQUIT  

	if (sigprocmask(SIG_BLOCK, &sigset, NULL)==-1) // Bloqueia os sinais no sigset
	{ 
		perror("sigprocmask");
		exit(1);
	}

	if(signal(SIGTERM, SIG_IGN)==SIG_ERR)//ignorar o SIGTERM
	{
		perror("signal");
		exit(1);
	}
	
		signal(SIGCHLD, myhandler);

		while(1) 
		{
			wait_something();

			pid_t r = fork();

			if(r == 0) {

				sigaddset(&sigset, SIGTSTP); // Acrescentar SIGTSTP

				if (sigprocmask(SIG_BLOCK, &sigset, NULL)==-1) 
				{
					perror("sigprocmask");
				}
				signal(SIGCHLD, SIG_DFL);
				do_something; 
				return(0);
			}    
			else
			{
				pid = wait(NULL);

				printf("Pid %d exited.\n", pid);	
			}
		}

		return(0);
	
}

void myhandler(int signum)
{
	printf("Received signal %d.\n", signum);
}		
