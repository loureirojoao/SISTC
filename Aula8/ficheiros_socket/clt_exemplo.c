#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void recv_server_reply1(int);
void recv_server_reply2(int);
int my_connect_to_server(char *servername, char *port);

int main (int argc, char* const argv[]) {

  if(argc!=3) {
    printf("Usage: %s server_ip_address port_number\n",argv[0]);
    exit(1); 
  }
    
  //read a string
  char buffer[4096];  
  printf("Enter a string: ");
  fgets(buffer, sizeof(buffer), stdin);
  
  
  //connect to server
  int socket_descriptor = my_connect_to_server(argv[1], argv[2]);
  
  
  //send string to server
  write(socket_descriptor, buffer, strlen(buffer));
  

  //Receive server reply. Check the difference between both versions of the routine.
  recv_server_reply1(socket_descriptor);
  //recv_server_reply2(socket_descriptor); 
  
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


 //version 1 - prints server reply as it receives it (by parts)
void recv_server_reply1(int s) 
{
  char buf[4096];

  printf("Reply from server: ");
  while(1) 
  {
    int n = read(s, buf, sizeof(buf)-1);
    if(n==0)
      break;
    buf[n] = 0;//terminate string (read does not do this)    
    fputs(buf, stdout);
    fflush(stdout);
  }
  

  printf("\n\n");
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
