#define _XOPEN_SOURCE 600
#include <signal.h>
#include "tlpi_hdr.h"

static char *str2; /* 保存第二个参数 */
static int handle = 0; /* 记录中断次数 */

void handler()
{
	crypt(str2, "xx"); /* crypt调用之后，字符串的匹配检查之前遭到信号处理器函数的中断，这时会发生字符串不匹配的情况 */
	handle++;
}

int main(int argc, char **argv)
{
	char *cr1;
	int callNum, misMatch;
	struct sigaction sa;

	if (argc != 3) {
		usageErr("%s arg1 arg2", argv[0]);
	}
	str2 = argv[2];
	cr1 = strdup(crypt(argv[1], "xx")); /* 使用strdup将结果复制到独立缓冲区,strdup需要释放内存 */
	if (cr1 == NULL) {
		errExit("strdup");
	}

	sigemptyset(&sa.sa_mask); /* 初始化空信号集 */
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) == -1) { /* 安装信号处理器 */
		errExit("sigaction");
	}

	for (callNum = 0, misMatch = 0; ; callNum++) {
		if (strcmp(crypt(argv[1], "xx"), cr1) != 0) {
			misMatch++;
			printf("misMatch on call %d (misMatch=%d handled=%d\n", callNum, misMatch, handle);
		}
	}

	return 0;
}