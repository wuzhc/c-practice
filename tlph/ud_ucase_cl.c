#include "ud_ucase.h"

int main(int argc, char const *argv[])
{
	struct sockaddr_un svaddr, claddr;
	int sfd, j;
	size_t msgLen;
	ssize_t numBtypes;
	char buf[BUF_SIZE];

	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		usageErr("%s msg... \n", argv[1]);
	}

	sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sfd == -1) {
		errExit("socket failed \n");
	}

	memset(&claddr, 0, sizeof(struct sockaddr_un));
	claddr.sun_family = AF_UNIX;
	snprintf(claddr.sun_path, sizeof(claddr.sun_path), "/tmp/ud_ucase_cl.%ld", (long)getpid());
	if (bind(sfd, (struct sockaddr *)&claddr, sizeof(struct sockaddr_un)) == -1) {
		errExit("bind failed \n");
	}

	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

	/* 客户端发送数据给服务端 */
	for (j=1;j<argc;j++) {
		msgLen = strlen(argv[j]);
		if (msgLen != sendto(sfd, argv[j], msgLen, 0, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un))) {
			fatal("sendto failed \n");
		}

		numBtypes = recvfrom(sfd, buf, BUF_SIZE, 0, NULL, NULL);
		if (numBtypes == -1) {
			errExit("recvfrom failed \n");
		}

		printf("Response %d: %.*s\n", j, (int)numBtypes, buf);
	}

	remove(claddr.sun_path);

	return 0;
}