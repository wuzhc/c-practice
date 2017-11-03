#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char **argv)
{
	int fd, flags, accessMode;
	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		usageErr("%s file \n", argv[1]);
	}

	fd = open(argv[1], O_WRONLY);
	if (fd != -1) {
		printf("[PID %ld] File \"%s\" already exists\n",
                (long) getpid(), argv[1]);
        close(fd);
	} else {
		printf("[PID %ld] File \"%s\" doesn't exist yet\n",
                    (long) getpid(), argv[1]);
        if (argc > 2) {             /* Delay between check and create */
            sleep(5);               /* Suspend execution for 5 seconds */
            printf("[PID %ld] Done sleeping\n", (long) getpid());
        }
		fd = open(argv[1], O_WRONLY | O_CREAT, S_IWUSR);
		if (fd == -1) {
			errExit("open %s failed \n", argv[1]);
		} else {
			 printf("[PID %ld] Created file \"%s\" exclusively\n",
                    (long) getpid(), argv[1]);          /* MAY NOT BE TRUE! */
		}

		/* 更改文件的状态标志 */
		flags = fcntl(fd, F_GETFL); /* 获取当前标志副本 */
		flags |= O_RDONLY;
		if (fcntl(fd, F_SETFL, flags) == -1) { /* fcntl失败返回-1 */
			errExit("fcntl");
		}

		flags = fcntl(fd, F_GETFL);
		if (flags == -1) {
			errExit("fcntl");
		}
		/* 判断文件是否以同步写方式打开 */
		if (flags & O_SYNC) {
			printf("write is sync \n");
		}
		/* 判断文件的访问模式 */
		accessMode = flags & O_ACCMODE; /* 先与O_ACCMODE相与 */
		if (accessMode == O_WRONLY) {
			printf("%s is writeable\n", argv[1]);
		}
		if (accessMode == O_RDONLY) {
			printf("%s is readable\n", argv[1]);
		}
	}
	return 0;
}