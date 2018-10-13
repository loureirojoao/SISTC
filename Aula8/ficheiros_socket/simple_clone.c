#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main (int argc, char* const argv[]) {
	char buf[4096];


	if(argc!=2)
	{
		printf("usage: %s source\n", argv[0]);
		return 1;
	}

	int fds = open(argv[1], O_RDONLY);
	if(fds == -1) {
		perror("open source");
		return 1;
	}

	char filename[15];
	strcpy(filename, "fileXXXXXX.bin");
	int fdd = mkstemps(filename, 4);
	if(fdd == -1){
		perror("open destination");	
		return 1;
	}

	while(1) {
		//read at most sizeof(buf) bytes from fp1 into buf
		int n = read(fds, buf, sizeof(buf));
		if(n == 0)
			break;

		//write n bytes contained in buf into fd
		write(fdd, buf, n);  
	}

	close(fds);
	close(fdd);

	printf("File %s created\n", filename);

	return 0;
}
