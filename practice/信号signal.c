#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

void error(char *msg)
{
    printf("%s : %s \n", msg, strerror(errno));
    exit(-1);
}

void handle(int sig)
{
    puts("Goodbye cruel world.......");
    exit(1);
}

int catch_signal(int sig, void (*handle)(int))
{
    struct sigaction action;
    action.sa_handler = handle;
    sigemptyset(&action.sa_mask); /* 用掩码过滤sigaction要处理的信号，通常会用一个空掩码 */
    action.sa_flags = 0; /* 附加标志位 */
    return sigaction(sig, &action, NULL);
}

int main(int argc, char *argv[])
{
    /* 需要捕获sigint信号 */
    if (catch_signal(SIGINT, handle) == -1) {
        error("catch signal failed");
    }

    char name[30];
    printf("Please input your name: \n");
    fgets(name, sizeof(name), stdin);
    printf("%s \n", name);

    return 0;
}
