#define _GNU_SOURCE
#include <signal.h>
#include "tlpi_hdr.h"

static volatile int allDone = 0;
static volatile int sigCnt = 0;
static volatile int handlerSleepTime; /* 信号处理器睡眠时间 */

/* 信号处理器函数 */
static void siginfoHandler(int sig, siginfo_t *si, void *ucontext)
{
	/* 如果信号是SIGINT或SIGTERM则退出程序 */
	if (sig == SIGINT || sig == SIGTERM) {
		allDone = 1;
		return ;
	}
	sigCnt++; /* 记录有多少个信号达到 */
	printf("catch signal %d\n", sig);
	printf("si_signo=%d, si_code=%d (%s) \n", si->si_signo, si->si_code, 
		(si->si_code == SI_USER) ? "SI_USER" : (si->si_code == SI_QUEUE) ? "SI_QUEUE" : "other");
	printf("si_value=%d\n", si->si_value.sival_int);
	printf("si_pid=%ld, si_uid=%ld\n", (long)si->si_pid, (long)si->si_uid);
	sleep(handlerSleepTime);
}

int main(int argc, char *argv[])
{
	struct sigaction sa;
	sigset_t preMask, blockMask;
	int sig;

	/* --help */
	if (argc > 1 && strcmp(argv[1], "--help") == 0) {
		usageErr("%s block-time [handler-sleep-time] \n", argv[0]);
	}
	printf("%s: PID is %ld\n", argv[0], (long)getpid());

	/* 信号处理器休眠时间 */
	handlerSleepTime = (argc > 2) ? getInt(argv[2], GN_NONNEG, "handler-sleep-time") : 1;

	/* 安装信号处理器 */
	sa.sa_sigaction = siginfoHandler;
	sa.sa_flags = SA_SIGINFO;
	sigfillset(&sa.sa_mask);
	for (sig = 0; sig < NSIG; sig++) {
		if (sig != SIGTSTP && sig != SIGQUIT) {
			sigaction(sig, &sa, NULL);
		}
	}

	/* 阻塞信号 */
	if (argc > 1) {
		sigfillset(&blockMask); /* 初始化一个包含所有信号的信号集 */
		sigdelset(&blockMask, SIGINT); 
		sigdelset(&blockMask, SIGTERM);

		/* 设置阻塞信号 */
		if (sigprocmask(SIG_SETMASK, &blockMask, &preMask) == -1) {
			errExit("sigprocmask failed \n");
		}

		printf("%s:signals blocked - sleeping %s seconds\n", argv[0], argv[1]);
		sleep(getInt(argv[1], GN_GT_0, "block-time"));
		printf("%s: sleep complete\n", argv[0]);

		/* 睡眠之后解除信号阻塞 */
		if (sigprocmask(SIG_SETMASK, &preMask, NULL) == -1) {
			errExit("sigprocmask failed 2 \n");
		}
	}

	while (!allDone) {
		pause();
	}
	return 0;
}