#include "us_xfr.h"
#define BACKLOG 5

int main(int argc, char *argv[])
{
	struct sockaddr_un addr; /* socket绑定地址的数据结构 */
	int sfd, cfd; /* socket file descriptor */
	ssize_t numRead;
	char buf[BUF_SIZE];

	sfd = socket(AF_UNIX, SOCK_STREAM, 0); /* 流socket */
	if (sfd == -1) {
		errExit("socket failed \n");
	}

	/* 当不需要socket时，使用remove删除 */
	if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
		errExit("remove failed \n");
	}

	memset(&addr, 0, sizeof(struct sockaddr_un)); /* 清空sockaddr_un数据结构为0 */
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1); /* 将SV_SOCK_PATH复制到addr.sun_path */

	if (bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
		errExit("bind failed \n");
	}

	if (listen(sfd, BACKLOG) == -1) {
		errExit("bind failed \n");
	}

	for (;;) {
		cfd = accept(sfd, NULL, NULL);
		if (cfd == -1) {
			errExit("accept failed \n");
		}

		while ((numRead = read(cfd, buf, BUF_SIZE)) > 0) {
			if (write(STDOUT_FILENO, buf, numRead) != numRead) {
				fatal("partial/failed write \n");
			}
		}
		if (numRead == -1) {
			errExit("read failed\n");
		}
		if (close(cfd) == -1) {
			errMsg("close failed \n");
		}
	}

	return 0;
}