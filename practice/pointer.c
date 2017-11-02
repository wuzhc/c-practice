#include <stdio.h>

int main(void)
{
    int i, arr[] = {4,5,7,8,9};
    int * const pa = arr;//注意const的位置：不是const int * pa，
    for (i=0;i<5;i++) {
        printf("%d ",*pa);
        pa++;
    }
}

//arr[i] = *(arr+i)
//地址是可以相加的
