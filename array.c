#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct Arr {
    int len; //array length
    int num; //current number
    int *head; //指向数组首地址的指针变量
} A;

void initArr(A *arr, int len);
bool append(A *arr, int value);
bool insert(A *arr, int pos, int value);
bool isFull(A *arr);

//初始化数组，主要是为了动态分配内存
void initArr(A *arr, int len) {
    arr->head = (int *)malloc(sizeof(int) * len);
    if (NULL == arr) {
        printf("初始化失败！");
        exit(-1);
    }
    arr->len = len;
    arr->num = 0;
}

//追加元素
bool append(A *arr, int value) {
    if (isFull(arr)) {
        return false;
    }
    arr->head[arr->num] = value;
    arr->num = arr->num + 1;
    return true;
}

//是否已经满了
bool isFull(A *arr) {
    if (arr->len <= arr->num) {
        return true;
    }
    return false;
}

//显示数组列表
void listArr(A *arr) {
    int i;
    printf("当前数组的元素为：");
    for(i=0;i<arr->num;i++) {
        printf("%d ", arr->head[i]);
    }
}

//插入数组
bool insert(A *arr, int pos, int value) {

}

int main(void) {
    int len; A arr; int val; int i;
    printf("请输入数组的长度：");
    scanf("%d", &len);
    initArr(&arr, len);

    printf("你可以输入%d个值:\n", len);
    for(i=0;i<len;i++) {
        int result = scanf("%d", &val);
        if (result) {
            append(&arr, val);
        }
    }
    listArr(&arr);
    return 0;
}
