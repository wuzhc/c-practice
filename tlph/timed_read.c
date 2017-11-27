#include <signal.h>
#include "tlpi_hdr.h"
#define BUF_SIZE 200

static void handler(int sig)
{
	printf("catch signal\n");
}

int main(int argc, char *argv[])
{
	struct sigaction sa;
	char buf[BUF_SIZE];
	ssize_t numRead;
	int saveErrno;

	if (argc > 1 && strcmp(argv[1], "--help") == 0) {
		usageErr("%s [num-secs [restart-flag]]\n", argv[0]);
	}

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = (argc > 2) ? SA_RESTART : 0; /* 系统调重新启动标识 */
	sa.sa_handler = handler;
	if (sigaction(SIGALRM, &sa, NULL) == -1) {
		errExit("sigaction \n");
	}

	/* 定时器,默认为5秒 */
	alarm((argc > 1) ? getInt(argv[1], GN_NONNEG, "num-secs") : 5);

	/* read阻塞调用 */
	numRead = read(STDIN_FILENO, buf, BUF_SIZE - 1);
 
	saveErrno = errno;
	alarm(0); 
	errno = saveErrno;

	if (numRead == -1) {
		if (errno == EINTR) {
			printf("read time out\n");
		} else {
			errExit("read \n");
		}
	} else {
		printf("successful read (%ld bytes):%.*s\n", (long)numRead, (int)numRead, buf);
	}
	return 0;
}