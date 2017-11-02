#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main (int argc, char **argv)
{
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];


	/* 参数检测 */
	if (argc != 3 || strcmp(argv[1], "--help")) {
		usageErr("%s old-filename new-filename \n", argv[0]);
	}

	inputFd = open(argv[1], O_RDONLY); 
	if (inputFd == -1) {
		errExit("open file %s \n", argv[1]);
	}

	openFlags = O_WRONLY | O_CREAT | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	outputFd = open(argv[2], openFlags, filePerms); /* open 失败返回-1 */
	if (outputFd == -1) {
		errExit("open file %s \n", argv[2]);
	}

	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) { /* read 返回读取字节数，失败是返回-1 */
		if (write(outputFd, buf, numRead) != numRead) { /* write 返回写入的字节数 */
			fatal("could't write whole buffer");
		}
	}
	if (numRead == -1) {
		errExit("read failed");
	}

	if (close(inputFd) == -1) {
		errExit("close input failed");
	}
	if (close(outputFd) == -1) {
		errExit("close output failed");
	}

	exit(EXIT_SUCCESS);
	return 0;
}
