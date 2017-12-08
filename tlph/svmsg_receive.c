#define _GNU_SOURCE /* 获取MSG_EXCEPT定义 */
#include <sys/types.h>
#include <sys/msg.h>
#include "tlpi_hdr.h"
#define MAX_MTEXT 1024

struct mbuf {
	long mtype;
	char mtext[MAX_MTEXT];
};

/* 命令行参数 ./svmsg_rcv -t type -e noerror -n IPC_NOWAIT -x MSG_EXCEPT */
void usageError(const char *program, const char *msg)
{
	if (msg != NULL) {
		fprintf(stderr, "%s\n", msg);
	}
	fprintf(stderr, "Usage: %s [options] msqid [maxBytes]\n");
	fprintf(stderr, "-t mtype Select message of given type \n");
	fprintf(stderr, "-e Use MSG_NOERROR flag\n");
	fprintf(stderr, "-n Use IPC_NOWAIT flag\n");
#ifdef MSG_EXCEPT
	fprintf(stderr, "-x Use MSG_EXCEPT flag\n");
#endif
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	struct mbuf msg;  /* message buffer for msgrcv */
	int msqid, flags, type;
	ssize_t maxLen;
	size_t maxBytes;
	char opt;

	type = 0;
	flags = 0;
	while ((ch=getopt(argc, argv, "t:enx")) != -1) {
		switch (ch) {
			case 't':
				type = atoi(optarg);
				break;
			case 'n':
				flags |= IPC_NOWAIT;
				break;
			case 'e':
				flags |= MSG_NOERROR;
				break;
#ifdef MSG_EXCEPT
			case 'x':
				flags |= MSG_EXCEPT;
				break;
#endif
			default:
				usageError(argv[0], "Bad options");
		}
	}

	/* 检测命令行参数个数 */
	if (argc < optind + 1 || argc > optind + 2) {
		usageError(argv[0], "Wrong number of arguments");
	}

	msqid = getInt(argv[optind], 0, "msqid");
	maxBytes = (argc > optind + 1) ? getInt(argv[optind+1], 0, "max-bytes") : MAX_MTEXT;

	msgLen = msgrcv(msqid, &msg, maxBytes, type, flags); /* return number of bytes copied into mtext field or -1 on error*/
	if (msgLen == -1) {
		errExit("msgrcv failed \n");
	}

	printf("Receive: type=%d; length=%ld;", msg.mtype, (long)msgLen);
	if (msgLen > 0) {
		printf(" body=%s", msg.mtext);
	}
	printf("\n");

	exit(EXIT_SUCCESS);
}