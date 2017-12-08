#include <sys/types.h>
#include <sys/msg.h>
#include "tlpi_hdr.h"

void usageError(char *program, char *msg)
{
	if (msg != NULL) {
		fprintf(stderr, "%s\n", msg);
	}
	fprintf(stderr, "Usage : %s msqid max-bytes\n", program);
	exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	struct msqid_ds ds;
	int msqid;

	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		usageError(argv[0], NULL);
	}

	msqid = getInt(argv[1], 0, "msqid");
	if (msgctl(msqid, IPC_STAT, &ds) == -1) {
		errExit("msgctl IPC_STAT failed \n");
	}
	ds.msg_qtypes = getInt(argv[2], 0, "max-bytes");
	if (msgctl(msqid, IPC_SET, &ds) == -1) {
		errExit("msgctl IPC_SET failed \n");
	}
	
	return 0;
}