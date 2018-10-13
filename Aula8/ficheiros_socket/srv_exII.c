#include <netinet/in.h>
#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h> //inet_ntoa

int create_server_socket(int port);


int main(int argc, char *argv[]){
	int new_socket_descriptor, socket_descriptor; 
	int n, r;
	unsigned int clilen;  
	struct sockaddr_in cli_addr;

	if(argc!=2) {
		printf("Usage: %s port_number\n", argv[0]);
		exit(1); 
	}

	//SIGPIPE is sent to the process if a write is made to a closed connection.
	//By default, SIGPIPE terminates the process. This makes the process to ignore the signal.
	signal(SIGPIPE, SIG_IGN);

	socket_descriptor = create_server_socket(atoi(argv[1]));

	while(1) {
		char c;
		char filename[1024];
		char buf[4096];

		printf("Waiting connection\n");  
		clilen = sizeof(cli_addr); 
		new_socket_descriptor = accept(socket_descriptor, (struct sockaddr *) &cli_addr, &clilen);  
		printf("Connection from %s\n", inet_ntoa(*((struct in_addr *) &(cli_addr.sin_addr) )));

		signal(SIGCHLD, SIG_IGN);

		r = fork();

		if(r==0){

			strcpy(filename,"fileXXXXXX.bin");
			int fdd = mkstemps(filename, 4);
			if(fdd == -1){
				perror("open destination");
				return 1;}

			//serve request (communication with the client)
			//On each iterartion, read one character, convert it to uppercase and send it back to the cliente 
			while(1)
			{
				n = read(new_socket_descriptor, buf, sizeof(buf));
				if (n==0)
					break;

				write(fdd, buf, n);				
			}

			close(new_socket_descriptor);
			exit(1);
		}

		close(new_socket_descriptor);
	}
	return 0;
}

int create_server_socket(int port)
{
	int s;
	struct sockaddr_in serv_addr;

	s = socket(PF_INET, SOCK_STREAM, 0);
	if(s < 0){
		perror("socket");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	if(bind(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		perror("bind");
		exit(1);
	}    

	listen(s, 5); 

	return s;
}

