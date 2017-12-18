#include "tlpi_hdr.h"
#define MAX_READ 20

int main(int argc, char *args[])
{
	char readBuf[MAX_READ+1];
	char writeBuf[] = "Please input somethings:\n";
	size_t numRead;

	/* write调用成功不能保证数据已写入磁盘，请参考文件IO缓冲 */
	if (write(STDOUT_FILENO, writeBuf, strlen(writeBuf)) != strlen(writeBuf)) {
		errExit("write failed \n");
	}

	numRead = read(STDIN_FILENO, readBuf, MAX_READ);
	if (numRead == -1) {
		errExit("read failed");
	}
	readBuf[numRead] = '\0'; /* 表示字符串中止需要一个字节*/
	printf("The input data was : %s\n", readBuf);

	exit(EXIT_SUCCESS);
}

