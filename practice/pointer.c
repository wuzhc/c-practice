#include <stdio.h>

int main(void)
{
    int i, arr[] = {4,5,7,8,9};
    int * const pa = arr;//ע��const��λ�ã�����const int * pa��
    for (i=0;i<5;i++) {
        printf("%d ",*pa);
        pa++;
    }
}

//arr[i] = *(arr+i)
//��ַ�ǿ�����ӵ�
