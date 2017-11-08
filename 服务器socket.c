#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/types.h>

int listener_d; /* 套接字 */
void error_exit(char *);
void handle_shutdown(int);
int catch_signal(int, void (*handle)(int));
int open_listener_socket();
void bind_to_port(int, int);
void listen_to_port(int, int);
void say(int, char *);
int read_in(int, char *, int);

int main(int argc, char *argv[])
{
    char *reply[] = {
        "one\r\n",
        "two\r\n",
        "three\r\n",
        "four\r\n"0
    };

    /* 安装信号捕捉 */
    if (catch_signal(SIGINT, handle_shutdown) == -1) {
        error_exit("Set signal failed");
    }

    /* 创建套接字 */
    listener_d = open_listener_socket();
    if (listener_d == -1) {
        error_exit("create sock stream failed");
    }

    bind_to_port(listener_d, 30000);
    listen_to_port(listener_d, 10);

    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    puts("waiting for connection");

    char buf[255]; /* 缓冲区，接收来自客户端内容 */
    while (1) {
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
        if (connect_d == -1) {
            error_exit("accept client failed");
        }

        /* fork子进程，由子进程处理accept创建的副套接字符 */
        if (!fork()) {
            close(listener_d); /* 子进程不需要这个，可以关闭 */
            char *msg = reply[rand() % 4];
            say(connect_d, msg);
            read_in(connect_d, buf, sizeof(buf));
            printf("from client : %s \n", buf);
            close(connect_d);
            exit(0); /* 通信结束之后，子进程退出程序*/
        }

        close(connect_d); /* 创建子进程后，关闭connect_d */
    }

    return 0;
}

void error_exit(char *msg)
{
    fprintf(stderr, "%s : %s \n", msg, strerror(errno));
    exit(1);
}

void handle_shutdown(int sig)
{
    if (listener_d) {
        close(listener_d);
    }

    fprintf(stderr, "\n%s\n", "Goodbye");
    exit(0);
}

int catch_signal(int sig, void (*handle)(int))
{
    struct sigaction action;
    action.sa_handler = handle;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

int open_listener_socket()
{
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    return listener_d;
}

void bind_to_port(int listener_d, int port)
{
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    /* 设置可以重新使用端口 */
    int reuse = 1;
    if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
        printf("Can not set the reuse option on the socket\n");
    }
    if (bind(listener_d, (struct sockaddr *)&name, sizeof(name)) == -1) {
        error_exit("Can not bind port");
    }
}

void listen_to_port(int listener_d, int num)
{
    if (listen(listener_d, num) == -1) {
        error_exit("Listen port failed");
    }
}

void say(int connect_d, char *msg)
{
    send(connect_d, msg, sizeof(msg), 0);
}

int read_in(int connect_d, char *buf, int len)
{
    char *s = buf;
    int slen = len;
    int c = recv(connect_d, s, slen, 0); /* 把内容读到buf缓冲区 */
    while (c > 0 && s[c - 1] != '\n') { /* 协议最末尾为\n表示结束，若没接收到所有字符，继续接收 */
        s += c; /* 移动buf地址 */
        slen -= slen; /* 读取长度减少 */
        recv(connect_d, s, slen, 0);
    }
    if (c < 0) {
        return c;
    } else if (c == 0) {
        buf[0] = '\0';
    } else {
        s[c-1] = '\0';
    }
    return len - slen;
}