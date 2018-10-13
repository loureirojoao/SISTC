#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <string.h>

int main()
{
	int status;
	char *ptr = malloc (8);
	char str1[] = "pai";

	strcpy(ptr,str1);	
	
	pid_t r = fork(); 
	if (r == 0) {
		char str2[]= "filho";
		strcpy(ptr,str2);
		printf("filho = %s\n\n", str2);
		return 0 ;
	}

	waitpid(r, NULL, 0); //Esperar especificamente
	//pelo processo "r"
	
	printf("ptr = %s\n", ptr);
}