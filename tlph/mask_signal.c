#include <stdio.h>
#include <signal.h>
#include "tlpi_hdr.h"

int main(int argc, char *args[])
{
	sigset_t blockSet, preMask;

	/* 初始化信号集，并包含SIGINT信号 */
	sigemptyset(&blockSet);
	sigaddset(&blockSet, SIGINT);

    /* 添加阻塞信号SIGINT,并保存之前的阻塞信号 */
	if (sigprocmask(SIG_BLOCK, &blockSet, &preMask) == -1)
		errExit("sigprocmask failed");

	/* 解除信号之后，会立刻将信号传递给进程 */
	if (sigprocmask(SIG_SETMASK, &preMask, NULL) == -1) 
		errExit("failed");

	return 0;
}