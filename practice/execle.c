#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *param[] = {"name=wuzhc", NULL}; /* ����������ʽ : ������ = ֵ���������һ�����ΪNULL */
    if (execle("test", "test", "45", "nnn", "yu", NULL, param) == -1) { /* ������������param�� */
        printf("%s", strerror(errno));
    }
    return 0;
}
