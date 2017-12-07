#include <wait.h>
#include <signal.h>
#include "tlpi_hdr.h"

/* 子进程退出SIGCHLD信号处理器 */
void sigchldHandle(int sig)
{
	printf("caught signal %d \n", sig);
}

int main(int argc, char *argv[])
{
	pid_t pid, childPid;
	int i, total;
	struct sigaction sa;

	/* 安装信号处理器 */
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigchldHandle;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		errExit("sigaction failed \n");
	}

	/* 创建子进程 */
	printf("parent pid = %d\n", getpid());

	//setbuf(stdout, NULL);

	for (i=0; i<5; i++) {
		switch(pid = fork()){
			case -1:
				errExit("fork failed \n");
				break;
			case 0:
				printf("child pid = %d\n", getpid());
				//_exit(EXIT_SUCCESS);
				break;
			default:
				break;
		}
	}

	total = 0;
	for (;;) {
		childPid = wait(NULL);
		if (childPid == -1) {
			if (errno == ECHILD) {
				printf("no more children - bye\n");
				break;
			} else {
				errExit("wait failed");
			}
		}
		total++;
	}

	printf("%d child process exit\n", total);
	// exit(EXIT_SUCCESS);
}