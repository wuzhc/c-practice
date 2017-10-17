#include <stdio.h>

/* 数组排序 */
void array_sort(int arr[], int len);

int main()
{
     /* 寻找数组中任意两个元素之后等于指定数 */
    printf("寻找数组中任意两个元素之后等于指定数：\n");

    int arr[] = {45,36,7,86,74,54,55,12,78};
    int i;
    int len = sizeof(arr)/ sizeof(arr[0]);

    /* 从小到大排序数组 */
    printf("排序后的数组\n");
    array_sort(arr, len);
    for (i=0;i<len;i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    int targetNum = 90;
    int begin = 0; //开始位置
    int end = len - 1; //结束位置
    while (begin < end) {
        int sum = arr[begin]+arr[end];
        if (sum > targetNum) {
            end--;
        } else if (sum < targetNum) {
            begin++;
        } else {
            printf("%d+%d=%d\n", arr[begin], arr[end], targetNum);
            begin++;
            end--;
        }
    }
    printf("\n\n");


    /* 3-sum */
    printf("寻找数组中任意三个元素之后为0：\n");
    int arr2[] = {-1,-2,-3,0,1,2,3};
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    int j,n,sum2;

    /* 从小到大排序数组 */
    printf("排序后的数组\n");
    array_sort(arr2, len2);
    for (j=0;j<len2;j++) {
        printf("%d ", arr2[j]);
    }
    printf("\n\n");

    for (n=0; n < len-1; n++) {
        int begin2 = n+1;
        int end2 = len2 - 1;
        while (begin2 < end2) {
            sum2 = arr2[begin2] + arr2[end2] + arr2[n];
            if (sum2 > 0) {
                end2--;
            } else if (sum2 < 0) {
                begin2++;
            } else {
                printf("%d+%d+%d=%d\n", arr2[n], arr2[begin2], arr2[end2], 0);
            begin2++;
            end2--;
            }
        }
    }

    return 0;
}

//排序
void array_sort(int arr[], int len)
{
    int i,j,temp;
    for (i=0; i<len-1; i++) {
        for (j=i+1; j<len; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
