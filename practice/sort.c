#include <stdio.h>

void sort_arr(int * a, int len);

int main()
{
    int arr[] = {45,8,78,0,0,-4,55,64,23};
    int len, i;

    len = sizeof(arr) / sizeof(int);

    printf("排序前的数组：\n");
    for (i=0;i<len;i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    sort_arr(arr, len);
    printf("排序后的数组：\n");
    for (i=0;i<len;i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

}

void sort_arr(int *a, int len)
{
    int tmp, i, j;
    for (i=0;i<len;i++) {
       for (j=i+1;j<len;j++) {
            if (a[i] > a[j]) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}
