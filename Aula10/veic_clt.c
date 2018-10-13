#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <netinet/in.h>
#include <netdb.h>

#define VEHIC_MAXPLEN 81
typedef struct {
	char plate[6];
	char owner[VEHIC_MAXPLEN];
	double value;
} vehic_t;

void vehic_read(vehic_t *v);
void vehic_print(vehic_t *v);
int vehic_menu();
int my_connect_to_server(char *servername, char *port);
void recv_server_reply2(int s);
void ex3_error(int s);


int main (int argc, char* const argv[]) {
	int op;
	char buffer[4096];
	//int n;
	char string[4096];
	vehic_t v;

	char http_msg1[] = "POST /~jes/sistc/pl/ws/vehicle-error.php HTTP/1.1\r\n"
		"Host: ave.dee.isep.ipp.pt\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"Connection: close\r\n"
		"Content-Length: ";

	char http_msg2[] = "GET /~jes/sistc/pl/ws/vehicles.php?o=JSON HTTP/1.1\r\n"
		"Host: ave.dee.isep.ipp.pt\r\n"
		"Connection: close\r\n\r\n";

	while(1) {
		op = vehic_menu();
		switch(op) {
			case 0: exit(1);
			case 1:
				vehic_read(&v);

				sprintf(buffer,"plate=%.6s&owner=%s&value=%.2lf",v.plate,v.owner,v.value);

				sprintf(string,"%s %ld\r\n\r\n%s",http_msg1,strlen(buffer),buffer);

				int s = my_connect_to_server("ave.dee.isep.ipp.pt", "80");

				//send new record to server
				write(s, string, strlen(string));
				puts(string);

				//recv_server_reply2(s);
				ex3_error(s);
				break;
			case 2:

      s = my_connect_to_server("ave.dee.isep.ipp.pt","80");
      write(s, http_msg2, strlen(http_msg2));

      //Variáveis "dadas" -> Perguntar ao prof porque é que
      //                     ist não podes estar antes do my_connect...
      char c;
      vehic_t v;
      char buffer2[8192];
      int nchars;
      int state = 0;
			char buffer3[8192];
			int n;



    while((n = read(s, buffer3, sizeof(buffer3)))>0){
    //int n = read(s,buffer2, 500);

      int i;
      for (i=0;i<n;i++){
        c = buffer3[i];


      switch(state) {
          case 0:
          case 2:
          case 4:
      if( c == '"' ) { //found opening "
        state++;
        nchars = 0;
        break;
      }

      if( c == '['  && state != 0 ) { //new record before completing current one
        printf("invalid record\n");
        state = 0;
        break;
      }

      break;

          case 1://reading plate
      if( c == '"' ) {  //found closing "
        state = 2;
        break;
      }

      if( nchars == 6 ) //discard unexpected chars
        break;

      v.plate[nchars++] = c;
      break;

          case 3://reading owner
      if( c == '"' ) { //found closing "
        state = 4;
        v.owner[nchars] = 0;
        break;
      }

      if( nchars == VEHIC_MAXPLEN-1 ) //discard unexpected chars
        break;

      v.owner[nchars++] = c;
      break;

          case 5://reading value
      if( c == '"' ) { //found closing "
        state = 0;

        buffer2[nchars] = 0;
        v.value = atof(buffer2);
        vehic_print(&v);

        break;
      }

      if( nchars == sizeof(buffer2)-1 ) //discard unexpected chars
        break;

      buffer2[nchars++] = c;
      break;
  }
}
}
      break;
      }
}
return 0;
}

//do not change code below!!

int vehic_menu() {
	int op;
	printf("\n0 - Exit\n");
	printf("1 - Insert new record\n");
	printf("2 - Print all\n");
	printf("\nEnter option: ");
	fflush(stdout);
	scanf("%d", &op);
	getchar(); //consume '\n'
	printf("\n");

	return op;
}

void vehic_read(vehic_t *v) {
	char buf[VEHIC_MAXPLEN];

	printf("Plate (6 characters): ");
	fgets(buf, VEHIC_MAXPLEN, stdin);
	memcpy(v->plate, buf, 6);
	printf("Owner: ");
	fgets(v->owner, VEHIC_MAXPLEN, stdin);
	v->owner[strlen(v->owner)-1] = 0; //"move" the end of the string to the place of '\n'
	printf("Value: ");
	scanf("%lf", &v->value);
	getchar(); //consume \n
}

void vehic_print(vehic_t *v) {
	v->owner[VEHIC_MAXPLEN-1] = 0;//double check
	printf("%.6s - %s - %.2lf\n", v->plate, v->owner, v->value);
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

void ex3_error(int s){
	char buf[16384];
	char *ptr, *ptr2;
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

	if ( (ptr = strstr(buf, "<ws-error>")) !=NULL)
	{
		//ptr fica a apontar para o primeiro caracter da mensagem de erro
		ptr = strstr(ptr, ">") +1;

		//função strset substitui o '<' de "</ws-error>" pelo fim de string
		ptr2 = ptr;
		ptr = strsep (&ptr2, "<");

		printf("Error message from server: \"%s\"\n\n", ptr);
	}

}

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
