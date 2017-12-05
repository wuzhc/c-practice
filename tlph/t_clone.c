#define _GNU_SOURCE
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sched.h>
#include "tlpi_hdr.h"

#ifndef CHILD_SIG
#define CHILD_SIG SIGUSR1 /* clone进程时会生成终止信号 */
#endif

/* 克隆产生的子进程从childFunc处开始执行 */
static int childFunc(void *arg)
{
	if (close(*((int *)arg)) == -1) { /* 将void*转为int*，关闭文件描述符 */
		errExit("close failed \n");
	}
	return 0; /* return 子进程终止，返回值为进程退出状态 */
}

int main(int argc, char *argv[])
{
	const int STACK_SIZE = 65536; /* 栈大小 */
	char *stack; 
	char *stackTop;
	int fd, flags;

	fd = open("/dev/null", O_RDWR);
	if (fd == -1) {
		errExit("open failed \n");
	}

	/* 命令行参数大于1时，设置父子进程共享打开文件描述符表 */
	flags = argc > 1 ? CLONE_FILES : 0;

	/* 为子进程分配栈空间 */
	stack = malloc(STACK_SIZE);
	if (stack == NULL) {
		errExit("malloc failed \n");
	}
	stackTop = stack + STACK_SIZE;

	/* 忽略非SIGCHLD信号 */
	if (CHILD_SIG != 0 && CHILD_SIG != SIGCHLD) {
		if (signal(CHILD_SIG, SIG_IGN) == SIG_ERR) {
			errExit("signal failed \n");
		}
	}

	/* clone先去执行childFunc，return时发送CHILD_SIG给*/
	if (clone(childFunc, stackTop, flags | CHILD_SIG, (void *)fd) == -1) {
		errExit("clone failed \n");
	}

	if (waitpid(-1, NULL, (CHILD_SIG == SIGCHLD) ? 0 : __WCLONE) == -1) {
		errExit("waitpid failed \n");
	}

	s = write(fd, "x", 1);
	if (s == -1 && errno == EBADF) {
		printf("file descriptor %d has been closed\n", fd);
	} else if (s == -1) {
		printf("write() on file descriptor %d failed with (%s)\n", fd, strerror(errno));
	} else {
		printf("write() on file descriptor %d successfully \n", fd);
	}

	return 0;
}