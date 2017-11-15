#include <signal.h>
#include "tlpi_hdr.h"

int main(int argc, char *args[])
{
	int sig, res;
	if (argc != 3 || strcmp(args[1], "--help") == 0) {
		usageErr("%s pid sig", args[0]);
	}

	sig = getInt(args[2], 0, "sig-num");

	/* kill发送信号,失败返回-1,成功返回0 */
	res = kill(getLong(args[1], 0, "pid-num"), sig);

	if (sig == 0) { /* sig为0为空信号，用于检测特定进程是否存在 */
		if (res == 0) { /* kill调用成，说明进程存在 */
			printf("process exists and we can send it a singal \n");
		} else {
			if (errno == EPERM) { /* 进程存在，但没有权限*/
				printf("process exists, but we don't have permission to send it a singal \n");
			} else if (errno == ESRCH) { /* 进程不存在 */
				printf("process doesn't exists \n");
			} else {
				errExit("kill failed");
			}
		}
	} else {
		if (res == -1) {
			errExit("kill failed");
		}
	}

	exit(EXIT_SUCCESS);
	return 0;
}