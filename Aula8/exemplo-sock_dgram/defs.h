#define RECEIVER_NAME    "sistc_sock1"

#define MAX_TEXT_SIZE 256

typedef struct {
	pid_t pid;
	char text[MAX_TEXT_SIZE];
} chatmsg_t;

