#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <sys/sendfile.h>


int my_connect_to_server(struct addrinfo *addr) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1)
  {
    perror("socket");  
    exit(1);
  }
  
  if (connect(s, addr->ai_addr, addr->ai_addrlen) == -1)
  {
    perror("connect");  
    close(s);
    exit(2);
  }
  return s;
}

int main (int argc, char* const argv[]) {
	
  if(argc!=4) {
    printf("Usage: %s server_ip_address port_number\n",argv[0]);
    exit(1); 
  }

  char buf[4096];

  
  struct addrinfo hints;
  struct addrinfo *addrs;
  //memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;          /* Any protocol */


  int r = getaddrinfo(argv[1], argv[2], &hints, &addrs);
  if (r != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
    exit(0);
  }   
    FILE *fp = fopen(argv[3], "r");
    if(fp == NULL) {
    perror("fopen");
    exit(1);
  }
    int s = my_connect_to_server(addrs);
		
	     
    while(1) {
    //le os dados do fp e coloca-os no buffering
    int n = fread(buf, 1, sizeof(buf), fp);
    if(n == 0)
      break;
   printf("%s",buf);
    write(s, buf, strlen(buf));
  }  
 

fclose(fp);
  
  
  return 0;
}



