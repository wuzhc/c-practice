#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"

void usageError(const char *progName, const char *msg)
{
	if (msg != NULL) {
		fprintf(stderr, "%s\n", msg);
	}
	fprintf(stderr, "Usage: %s [-cxfkp] {-f pathname | -k key | -p [octa-perms]}\n", progName);
	fprintf(stderr, "	-c  		Use IPC_CREAT flag\n");
	fprintf(stderr, "	-x  		Use IPC_EXCL flag\n");
	fprintf(stderr, "	-f pathname Generate key using ftok()\n");
	fprintf(stderr, "	-k key 		Use 'key' as key\n");
	fprintf(stderr, "	-p 			Use IPC_PRIVATE key\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	char ch;
	int flags;
	key_t key;
	long lkey;
	int msqid; /* ipc对象标识符 */
	unsigned int perms; /* 权限 */

	/* 处理命令行参数 */
	while ((ch=getopt(argc, argv, "cxf:k:p")) != EOF) {
		switch (ch) {
			case 'c':
				flags |= IPC_CREAT;
				break;
			case 'x':
				flags |= IPC_EXCL;
				break;
			case 'f':
				key = ftok(optarg, 1);
				if (key == -1) {
					errExit("ftok failed\n");
				}
				break;
			case 'k':
				if (sscanf(optarg, "%li", &lkey) != 1) {
					cmdLineErr("-k option require a numeric argument \n");
				}
				key = lkey;
				break;
			case 'p':
				key = IPC_PRIVATE;
				break;
			default:
				usageError(argv[0], "Bad option");
		}
	}

	if (optind < 1) {
		usageError(argv[0], "Exactly one of the options must be supplied");
	}

	if (optind == argc) {
		perms = S_IRUSR | S_IWUSR;
	} else {
		perms = getInt(argv[optind], GN_BASE_8, "octa-perms");
	}

	msqid = msgget(key, flags | perms); /* 创建IPC对象，成功返回key标识符 */
	if (msqid == -1) {
		errExit("msgget failed \n");
	}

	printf("%d", msqid);
	exit(EXIT_SUCCESS);
}