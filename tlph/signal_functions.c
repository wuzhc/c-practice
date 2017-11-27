#define _GNU_SOURCE
#include <signal.h>
#include "tlpi_hdr.h"
#include "signal_functions.h"

void printSigset(FILE *f, const char *prefix, const sigset_t *sigset)
{
	int sig, count = 0;
	for (sig = 1; sig < NSIG; sig++) { /* NSIG 信号最大编号加1 */
		if (sigismember(sigset, sig)) { /* 测试sig是否为sigset信号集的成员 */
			fprintf(f, "%s%d (%s)\n", prefix, sig, strsignal(sig));
			count++;
		}
	}

	if (count == 0)
		fprintf(f, "%s <empty sigset> \n", prefix);
}

/* 显示进程的信号掩码 */
int printSigMask(FILE *f, const char *msg)
{
	sigset_t currMask; /* 当前进程阻塞的信号 */
	if (msg != NULL) {
		fprintf(f, "%s\n", msg);
	}
	if (sigprocmask(SIG_BLOCK, NULL, &currMask) == -1) { /* 将阻塞信号放到了currMask,sigprocmask还可以修改进程掩码 */
		return -1;
	}
	printSigset(f, "\t\t", &currMask);
	return 0;
}

/* 当前处于等待的信号集 */
int printPendingSigs(FILE *f, const char *msg)
{
	sigset_t pendingSigs; 
	if (msg != NULL) {
		fprintf(f, "%s\n", msg);
	}
	if (sigpending(&pendingSigs) == -1) { 
		return -1;
	}
	printSigset(f, "\t\t", &pendingSigs);
	return 0;
}
