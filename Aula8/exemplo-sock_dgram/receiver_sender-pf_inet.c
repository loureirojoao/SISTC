//SOCK_DGRAM Sender

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "defs.h"

int
main (int argc, char *argv[])
{
  int sd, rc;
  struct sockaddr_in serveraddr, clientaddr;
  socklen_t clientaddrlen;
  chatmsg_t msg;
  int port;
  
  if(argc!=2) {
    printf("Usage: %s port_number\n",argv[0]);
    exit(1); 
  }
  
  port = atoi(argv[1]);

  sd = socket(PF_INET, SOCK_DGRAM, 0);
  if (sd < 0)
  {
    perror("socket() failed");
    exit(1);
  }


  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(port);

  rc = bind(sd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if (rc < 0)
  {
    perror("bind() failed");
    exit(1);
  }

  while(1) {
    clientaddrlen = sizeof(clientaddr);
    rc = recvfrom(sd, &msg, sizeof(msg), 0,
                  (struct sockaddr *)&clientaddr,
                  &clientaddrlen);
    if (rc < 0)
    {
      perror("recvfrom() failed");
      exit(1);
    }

    printf("Message from %s, port %u\n", inet_ntoa(*((struct in_addr *) &(clientaddr.sin_addr))), ntohs(clientaddr.sin_port));
    printf("From %d: %s", msg.pid, msg.text);

    msg.pid = getpid();
    
    rc = sendto(sd, &msg, sizeof(msg), 0,
                (struct sockaddr *)&clientaddr,
                sizeof(clientaddr));
    if (rc < 0)
    {
      perror("sendto() failed");
      exit(1);
    }
  }

  return 0;
}
