#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FIFO_NAME "sistc_fifo"
#define MAXSZ 16

int open_fifo(char *, int);
void receive_print_v1(int fd);//no line discipline
void receive_print_v2(int fd);//line discipline by reading one byte at a time
void receive_print_v3(int fd);//line discipline with auxiliary buffer

int main() {
  int fd = open_fifo(FIFO_NAME, O_RDONLY);
  if( fd == -1 ) {
    perror("open_fifo");
    exit(1);
  }
  printf("Fifo open for reading\n\n");  
  
  receive_print_v1(fd);
}

void receive_print_v1(int fd)
{
  int n;
  char buffer[MAXSZ];
    
  while(1) {
    n = read(fd, buffer, MAXSZ-1); 
    if(n > 0) {
      buffer[n] = 0;
      printf("New message (%d bytes): %s\n", n, buffer);
      sleep(1);
    } 
    else   
      sleep(1);
  }
}  

void receive_print_v2(int fd)
{
  int n;
  char buffer[MAXSZ];
  char *pos = buffer;
  while(1) {
    n = read(fd, pos, 1); 
    if(n > 0) {
      if(*pos == '\n')
      {
        pos[1] = 0; //terminate string
        printf("New message (%ld bytes): %s\n", strlen(buffer), buffer);
        pos = buffer;
        sleep(5);        
      }
      else
        ++pos;
    }
    else
      sleep(1);
  }
}

void receive_print_v3(int fd)
{
  int n;
  char buffer[MAXSZ];
  char buffer2[MAXSZ];
  char *pos = buffer2;

  while(1) {
    n = read(fd, buffer, MAXSZ-1); 
    if(n > 0) {
      for(int i = 0; i < n; ++i) {
        *pos = buffer[i];
        if(*pos == '\n')
        {
          pos[1] = 0; //terminate string
          printf("New message (%ld bytes): %s\n", strlen(buffer2), buffer2);
          pos = buffer2;
          sleep(5);
        }
        else
          ++pos;
      }
    }    
    else
      sleep(1);
  }
}


int open_fifo(char *name, int flags) {
  struct stat st;
  
  //create fifo, if no file with that name exists or if existing file is not a fifo (man 7 inode)
  if( stat(name, &st) == -1  || S_ISFIFO(st.st_mode) == 0) {
    unlink(name);
    if( mkfifo(FIFO_NAME, 0600) == -1 ) {
      return -1;
    }
    else
      printf("Named pipe %s created\n", name );
  }  
    
  printf("Opening pipe and waiting for connection on remote endpoint\n");  
  return open(FIFO_NAME, flags);
}
