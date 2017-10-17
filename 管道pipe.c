#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void error(char *msg)
{
    printf("%s : %s \n", msg, strerror(errno));
    exit(-1);
}

int main(int argc, char *argv[])
{
    char msg[255];
    int pid_status;

    int fd[2];
    if (pipe(fd) == -1) {
        error("create pipe failed");
    }

    pid_t pid = fork();
    if (pid == -1) {
        error("fork failed");
    }

    FILE *f = fopen("output.txt", "a");
    if (f == -1) {
        error("open output.txt failed");
    } else {
        dup2(fileno(f), 1); /* 所有标准输出重定向到文件 */
    }

    if (!pid) {
        dup2(fd[1], 1); /* 把管道写入端连接到标准输出 */
        close(fd[0]); /* 关闭管道读取端 */
        printf("something output \n");
    } else {
        dup2(fd[0], 0); /* 管道读取端连接到标准输入 */
        close(fd[1]);

        printf("from parent process \n");
        while (fgets(msg, sizeof(msg), stdin)) {
            printf("%s \n", msg); /* 子进程的输出重定向到output.txt文件 */
        }

        wait_pid(pid, &pid_status, 0);
    }

    return 0;
}
