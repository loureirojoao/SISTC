#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void recv_server_reply1(int);
void recv_server_reply2(int);
int my_connect_to_server(char *servername, char *port);

int main (int argc, char* const argv[]) {

	char buffer[4096];  

	if(argc!=4) {
		printf("Usage: %s server_ip_address port_number\n",argv[0]);
		exit(1); 
	}

	//read a string

	//printf("Enter a string: ");
	//fgets(buffer, sizeof(buffer), stdin);

	//connect to server
	int socket_descriptor = my_connect_to_server(argv[1], argv[2]);

	int fds = open(argv[3], O_RDONLY);
	if(fds == -1) {
		perror("open source");
		return 1;
	}

	while(1) {
		//read at most sizeof(buf) bytes from fp1 into buf
		int n = read(fds, buffer, sizeof(buffer));
		if(n == 0)
			break;
		
		//write(fds, buffer, n);
		
	}

	close(fds);

	return 0;
}

int my_connect_to_server(char *servername, char *port) {


	//get server address
	struct addrinfo hints;
	struct addrinfo *addrs;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0; /* Any protocol */
	int r = getaddrinfo(servername, port, &hints, &addrs);
	if (r != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
		exit(1);
	}


	//create socket
	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1)
	{
		perror("socket");  
		exit(2);
	}

	//connect to server
	if (connect(s, addrs->ai_addr, addrs->ai_addrlen) == -1)
	{
		perror("connect");  
		close(s);
		exit(3);
	}

	return s;
}

//version 2 - receives whole answer and then prints it  
void recv_server_reply2(int s) 
{
	char buf[4096];

	int bytes_recv = 0;
	while(1) 
	{
		int n = read(s, buf + bytes_recv, sizeof(buf) - 1 - bytes_recv);
		if(n==0)
			break;

		bytes_recv += n;
	}

	buf[bytes_recv] = 0;//terminate string (read does not do this)
	printf("Reply from server: %s\n\n", buf);
}
