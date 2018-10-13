#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define FIFO_NAME "sistc_fifo"
#define MAXSZ 65536

int open_fifo(char *, int);

int main() {
  int fd, n;
  long sz;
  char buffer[MAXSZ];    

  fd = open_fifo(FIFO_NAME, O_WRONLY);
  if( fd == -1 ) {
    perror("open_fifo");
    exit(1);
  }
  printf("Fifo open for writing\n\n");  
    
  while(1) {
    printf("\nType message > ");
    fgets(buffer, MAXSZ, stdin);
    sz = strlen(buffer);
    n = write(fd, buffer, sz); 
    if(n != sz)
      perror("write");

    printf("%ld bytes written\n", sz);
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
