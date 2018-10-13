//SOCK_DGRAM Receiver

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

#include "defs.h"


int main(int argc, char *argv[]) {
  int    sd, rc;
  struct sockaddr_in serveraddr;
  time_t currtime;
  chatmsg_t msg;
  msg.pid=getpid();

  int port;
  struct hostent* hostinfo;  
  
  if(argc!=3) {
    printf("Usage: %s server_ip_address port_number\n",argv[0]);
    exit(1); 
  }
  
  hostinfo = gethostbyname(argv[1]);  
  port = atoi(argv[2]);

  sd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sd < 0)
  {
    perror("socket() failed");
    exit(1);
  }


  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr = *((struct in_addr *) hostinfo->h_addr);
  serveraddr.sin_port = htons(port);

  /* producing the message */
  currtime = time(NULL);
  snprintf(msg.text, 256, "%s", ctime(&currtime));



  rc = sendto(sd, &msg, sizeof(msg), 0,
              (struct sockaddr *)&serveraddr,
              sizeof(serveraddr));
  if (rc < 0)
  {
    perror("sendto() failed");
    exit(1);
  }

  printf("Client %d sent msg at %s\n", msg.pid, msg.text);

  rc = read(sd, &msg, sizeof(msg));
  if (rc != sizeof(msg))
  {
    perror("sendto() failed");
    exit(1);
  }

  printf("Echo from server %d: %s\n", msg.pid, msg.text);
  return 0;
}
