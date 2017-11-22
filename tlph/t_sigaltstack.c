#define _GNU_SOURCE
#include <signal.h>
#include "tlpi_hdr.h"

/* 当内存引用失败时就会发出sigsevg信号,sigsevgHandler是它的处理器函数 */
void sigsegvHandler(int sig)
{
	int x; /* 保存在栈里的*/
	printf("caught signal %d (%s)\n", sig, strsignal(sig)); /* printf是不安全函数，不建议在信号处理器使用 */
	printf("Top of handler stack near  %10p\n", &x); /* 处理程序栈的顶部 */
	fflush(NULL);
	_exit(EXIT_FAILURE);
}

void overflowStack(num)
{
	char a[100000];
	printf("Call %4d - Top of stack near %10p\n", num, &a[0]);
	overflowStack(num + 1);
}

int main(int argc, char **argv)
{
	stack_t sigstack; /* 改数据结构描述新备选信号栈的位置及属性 */
	struct sigaction sa;
	int j;

	printf("Top of standard stack near %10p\n", &j); /* 标准程序栈顶部 */
	sigstack.ss_sp = malloc(SIGSTKSZ); /* 备选栈位置 */
	if (sigstack.ss_sp == NULL) {
		errExit("malloc failed \n");
	}
	sigstack.ss_size = SIGSTKSZ; /* 备选栈大小 */
	sigstack.ss_flags = 0;

	/* 系统调用sigaltstack创建一个备选信号栈 */
	if (sigaltstack(&sigstack, NULL) == -1) {
		errExit("sigaltstack failed \n");
	}
	printf("Alternate stack is at %10p - %p \n",sigstack.ss_sp, (char *)sbrk(0) -1);

	/* 安装信号 */
	sa.sa_handler = sigsegvHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_ONSTACK;/* 使用由sigaltstack（）安装的备选栈 */
	if (sigaction(SIGSEGV, &sa, NULL) == -1) {
		errExit("sigaction failed \n");
	}

	overflowStack(1); /* 不断的递归，直到内存溢出，然后就可以产生sigsegv信号了 */
	return 0;
}