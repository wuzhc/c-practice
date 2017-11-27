#define _GNU_SOURCE
#include <signal.h>
#include <time.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

static volatile sig_atomic_t gotSigquit = 0;

void handler(int sig)
{
	printf("catch signal %d (%s)\n", sig, strsignal(sig));
	if (sig == SIGQUIT) {
		gotSigquit = 1;
	}
}

int main(int argc, char *argv)
{
	sigset_t blockMask, origMask;
	struct sigaction sa;
	int i;
	time_t startTime;

	/* 打印初始化信号 */
	printSigMask(stdout, "init signal is :\n");

	sigemptyset(&blockMask);
	sigaddset(&blockMask, SIGQUIT);
	sigaddset(&blockMask, SIGINT);

	/* 阻塞SIGINT和SIGQUIT信号 */
	if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1) {
		errExit("sigprocmask - SIG_BLOCK\n");
	}

	/* 安装信号处理器 */
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		errExit("sigaction - SIGNIT\n");
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1) {
		errExit("sigaction - SIGQUIT\n");
	}

	for (i = 0; !gotSigquit; i++) {
		printf("loop = %d\n", i);
		printSigMask(stdout, "starting critical section, signal mask is:\n");

		/* 模拟关键代码的执行 */
		for (startTime = time(NULL); time(NULL) < startTime + 4;) {
			continue;
		}
		
		/* 在关键代码执行过程中，触发信号，此时信号会被阻塞，放到等待对列 */
		printPendingSigs(stdout, "pending signal:\n");

		/* 解除阻塞，并等待信号,sigsuspend等信号处理器返回后，会把进程信号掩码恢复到调用前的值 */
		if (sigsuspend(&origMask) == -1 && errno != EINTR) {
			errExit("sigsuspend\n");
		}

		printSigMask(stdout, "after sigsuspend, signal mask is :\n");
	}

	/* 使用sigprocmask将信号掩码恢复为原始状态 */
	if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1) {
		errExit("sigprocmask - SIG_SETMASK");
	}

	printSigMask(stdout, "exit loop\n Restored signal mask to:\n");
	return 0;
}

