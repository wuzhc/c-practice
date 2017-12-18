#include "ud_ucase.h"

int main(int argc, char const *argv[])
{
	int sfd, i;
	char buf[BUF_SIZE];
	ssize_t numBtypes;
	socklen_t len;
	struct sockaddr_un svaddr, claddr;

	sfd = socket(AF_UNIX, SOCK_DGRAM, 0); /* 数据报 */
	if (sfd == -1) {
		errExit("socket failed \n");
	}

	if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
		errExit("remove failed \n");
	}

	memset(&svaddr, 0, sizeof(struct sockaddr_un));
	svaddr.sun_family = AF_UNIX;
	strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path) - 1);

	if (bind(sfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_un)) == -1) {
		errExit("bind failed");
	}

	for (;;) {
		len = sizeof(struct sockaddr_un);
		numBtypes = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *)&claddr, &len);
		if (numBtypes == -1) {
			errExit("recvfrom failed \n");
		}

		printf("Server received %ld bytes from %s\n", (long)numBtypes, claddr.sun_path);

		for (i = 0; i < numBtypes; ++i) {
			buf[i] = toupper((unsigned char)buf[i]);
		}

		if (sendto(sfd, buf, numBtypes, 0, (struct sockaddr *)&claddr, len) != numBtypes) {
			fatal("sendto");
		}
	}

	return 0;
}