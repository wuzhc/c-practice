#include <sys/types.h>
#include <sys/msg.h>
#include "tlpi_hdr.h"

void usageError(char *program, char *msg)
{
	if (msg != NULL) {
		fprintf(stderr, "%s\n", msg);
	}
	fprintf(stderr, "Usage : %s [msqid ...]\n", program);
	exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	int msqid, i;
	if (argc < 2) {
		usageError(argv[0], "Bad options");
	}

	for (i = 1; i < argc; i++) {
		msqid = getInt(argv[i], 0, "msqid");
		if (msgctl(msqid, IPC_RMID, NULL) == -1) {
			errExit("msgctl %s\n", argv[i]);
		} else {
			printf("Rm msg-queue %d successfully\n", argv[i]);
		}
	}
	
	return 0;
}