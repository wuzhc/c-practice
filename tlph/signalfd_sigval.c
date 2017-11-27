/* 使用signalfd来读取信号（信号被阻塞） */
#include <sys/signalfd.h>
#include <signal.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
	sigset_t mask;
	int sfd, j;
	struct signalfd_siginfo fdsi;
	ssize_t s;

	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		usageErr("%s sig-num ...\n", argv[1]);
	}

	printf("%s: PID=%ld\n", argv[1], (long)getpid());

	sigemptyset(&mask);
	for (j=1;j<argc;j++) {
		sigaddset(&mask, atoi(argv[j]));
	}

	if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
		errExit("sigprocmask \n");
	}

	sfd = signalfd(-1, &mask, 0);
	if (sfd == -1) {
		errExit("signalfd \n");
	}

	for (;;) {
		/* 调用read时，如果没有信号正在等待，那么read将阻塞，知道信号到达 */
		s = read(sfd, &fdsi, sizeof(struct signalfd_siginfo));
		if (s != sizeof(struct signalfd_siginfo)) {
			errExit("read \n");
		}

		printf("%s:got signal %d\n", argv[0], fdsi.ssi_signo);
		if (fdsi.ssi_code == SI_QUEUE) {
			printf(";ssi_pid = %d", fdsi.ssi_pid);
			printf("ssi_int = %d", fdsi.ssi_int);
		}
		printf("\n");
	}

	return 0;
}