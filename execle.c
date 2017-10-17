#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *param[] = {"name=wuzhc", NULL}; /* 环境变量格式 : 变量名 = 值，数组最后一项必须为NULL */
    if (execle("test", "test", "45", "nnn", "yu", NULL, param) == -1) { /* 环境变量放在param中 */
        printf("%s", strerror(errno));
    }
    return 0;
}
