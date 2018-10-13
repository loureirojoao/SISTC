#include <netinet/in.h>
#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h> //inet_ntoa

int main (int argc, char* const argv[]) 
{
  char filename[4096];
  
  FILE *fp1 = fopen(argv[3], "r");
  if(fp1 == NULL) {
    perror("fopen");
    exit(1);
  }
  while(1) {
    //read at most sizeof(buf) bytes from fp1 into buf
    int n = fread(buf, 1, sizeof(buf), fp1);
    if(n == 0)
      break;
      
    //write n bytes contained in buf into fp2 
    fwrite(buf, 1, n, fp2);
  }

  //send string to server
  write(s, buf, strlen(buf));

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
  fclose(fp1);
  
  