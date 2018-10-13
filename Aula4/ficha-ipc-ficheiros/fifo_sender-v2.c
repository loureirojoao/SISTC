#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define FIFO_NAME "sistc_fifo"
#define MAXSZ 65536

int open_fifo(char *, int);
int slow_write(int, void *, int);

int main() {
  int fd, n;
  int16_t sz;// 16 bit integer (short int)
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
    sz = (short int) strlen(buffer);
    --sz;
    buffer[sz] = 0; //remove '\n'
    
    n = write(fd, &sz, sizeof(sz)); 
    if(n != sizeof(sz))
      perror("write");
#ifdef USE_SLOW_WRITE
    n = slow_write(fd, buffer, sz);
#else
    n = write(fd, buffer, sz);
#endif 
    if(n != sz)
      perror("write");

    printf("%ld + %d bytes written\n", sizeof(sz), sz);
  }
}

int slow_write(int fd, void *buf, int len) {
  int sent = 0;
  if(len <= 0)
    return len;
  while(sent != len && write(fd, buf + sent, 1) == 1)
    ++sent;
  return sent;
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


