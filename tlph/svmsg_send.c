#include <sys/types.h>
#include <sys/msg.h>
#include "tlpi_hdr.h"

void usageError(const char *progName, const char *msg)
{
	if (msg != NULL) {
		fprintf(stderr, "%s\n", msg);
	}
	fprintf(stderr, "Usage: %s [-n] msqid msg-type [msg-text]\n", progName);
	fprintf(stderr, "		-n Use IPC_NOWAIT flag \n", ); /* IPC_NOWAIT 非阻塞发送操作 */
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv)
{
	struct mbuf msg;
	char opt;
	int msqid, flags, msgLen;

	flags = 0;
	while ((opt=getopt(argc,argv,"n")) != -1) {
		if (opt=='n'){
			flags |= IPC_NOWAIT;
		} else {
			usageError(argv[0], "Bad options");
		}
	}

	/* 检测参数个数是否正确 */
	if (argc < optind + 2 || argc > optind + 3) {
		usageError(argv[0], "Wrong number of argument");
	}

	exit(EXIT_SUCCESS);
}