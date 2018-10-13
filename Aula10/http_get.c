#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_connect_to_server(char *servername, char *port);

int main (int argc, char* const argv[]) {

  char buffer[4096];
  char http_msg1[] = "GET /~jes/sistc/pl/ola.html HTTP/1.1\r\n"
    "Host: www.dee.isep.ipp.pt\r\n\r\n";
    
  int s = my_connect_to_server("ave.dee.isep.ipp.pt", "80");
  
  //send HTTP request
  write(s, http_msg1, strlen(http_msg1));

  //receive HTTP server reply and print it on standard output
  int n;
  while( ( n = read(s, buffer, sizeof(buffer)-1) ) > 0 ) {
    buffer[n] = 0;
    fputs(buffer, stdout);
  }
  printf("\n\n");
  
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
