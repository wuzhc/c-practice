#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1) { /* ����-1��ʾִ��ʧ�� */
        if (execlp("ipconfig", "ipconfig", NULL) == -1) {
            fprintf(stderr, "Cannot run ipconfig:%s \n", strerror(errno));
            return 1;
        }
        printf("continue"); /* һ��execִ�гɹ��������ֹͣ���У�������������execִ�гɹ�ʱ���ᱻִ�� */
    }
    return 0;
}
