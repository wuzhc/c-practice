#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1) { /* 返回-1表示执行失败 */
        if (execlp("ipconfig", "ipconfig", NULL) == -1) {
            fprintf(stderr, "Cannot run ipconfig:%s \n", strerror(errno));
            return 1;
        }
        printf("continue"); /* 一旦exec执行成功，程序会停止运行，所以这句代码在exec执行成功时不会被执行 */
    }
    return 0;
}
