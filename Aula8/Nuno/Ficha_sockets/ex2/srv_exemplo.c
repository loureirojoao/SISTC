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
#include <arpa/inet.h>
#include <signal.h>
#include <ctype.h>

int prepara_socket_servidor(int port);

int prepara_socket_servidor(int port)
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


int main(int argc, char *argv[]){
  int ns, s,a;
  unsigned int clilen;  
  struct sockaddr_in cli_addr;
  char buf[500];
  
  signal(SIGPIPE, SIG_IGN);
  
  if(argc!=2) {
    printf("Usage: %s port_number\n", argv[0]);
    exit(1); 
  }
       
  s = prepara_socket_servidor(atoi(argv[1]));

  	
  while(1) {
    
    printf("Waiting connection\n");  
    clilen = sizeof(cli_addr); 
    ns = accept(s, (struct sockaddr *) &cli_addr, &clilen);  
    printf("Connection from %s\n", inet_ntoa(*((struct in_addr *) &(cli_addr.sin_addr) )));
 
a = fork(); 
	 if (a == 0) {

       char filename[1024];
       strcpy (filename, "fileXXXXXX.bin");
       int fd = mkstemps(filename, 4);
	
    //Pedido do servidor
    	FILE *fp1=fdopen(ns,"r+");
	    FILE *fp2=fdopen(fd,"r+");
while(1)
    {
	int n = fread(buf, 1, sizeof(buf), fp1);
        if(n == 0)
        break;    
    	fwrite(buf, 1, n, fp2);
    }
 
	fclose(fp1);
	fclose(fp2);
	exit(-1);
    }

    close(ns);
  }
  
  return 0;
}



