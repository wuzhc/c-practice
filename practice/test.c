#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error(char *msg)
{
    fprintf(stderr, "%s : %s \n", msg, strerror(errno));
    exit(1);
}


int main(int argc, char *argv[])
{
    char *reply[] = {
        "one\r\n",
        "two\r\n",
        "three\r\n",
        "four\r\n"
    };

    /* 创建套接字 */
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1) {
        error("create sock stream failed");
    }

    /* 绑定30000端口 */
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    
    /* 设置可以重新使用端口 */
    int reuse = 1;
    if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1) {
        error("can not set the reuse option on the socket");
    }
    if (bind(listener_d, (struct sockaddr *)&name, sizeof(name)) == -1) {
        error("bind port failed");
    }

    /* 监听端口 */
    if (listen(listener_d, 2) == -1) {
        error("listen port failed");
    }

    puts("waiting for connection");

    /* 接受连接 */
    while (1) {
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
        if (connect_d == -1) {
            error("accept client failed");
        }

        char *msg = reply[rand() % 4];
        /* 发送消息到客户端 */
        send(connect_d, msg, strlen(msg), 0);
        close(connect_d);
    }

    return 0;
}
