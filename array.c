#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct Arr {
    int len; //array length
    int num; //current number
    int *head; //ָ�������׵�ַ��ָ�����
} A;

void initArr(A *arr, int len);
bool append(A *arr, int value);
bool insert(A *arr, int pos, int value);
bool isFull(A *arr);

//��ʼ�����飬��Ҫ��Ϊ�˶�̬�����ڴ�
void initArr(A *arr, int len) {
    arr->head = (int *)malloc(sizeof(int) * len);
    if (NULL == arr) {
        printf("��ʼ��ʧ�ܣ�");
        exit(-1);
    }
    arr->len = len;
    arr->num = 0;
}

//׷��Ԫ��
bool append(A *arr, int value) {
    if (isFull(arr)) {
        return false;
    }
    arr->head[arr->num] = value;
    arr->num = arr->num + 1;
    return true;
}

//�Ƿ��Ѿ�����
bool isFull(A *arr) {
    if (arr->len <= arr->num) {
        return true;
    }
    return false;
}

//��ʾ�����б�
void listArr(A *arr) {
    int i;
    printf("��ǰ�����Ԫ��Ϊ��");
    for(i=0;i<arr->num;i++) {
        printf("%d ", arr->head[i]);
    }
}

//��������
bool insert(A *arr, int pos, int value) {

}

int main(void) {
    int len; A arr; int val; int i;
    printf("����������ĳ��ȣ�");
    scanf("%d", &len);
    initArr(&arr, len);

    printf("���������%d��ֵ:\n", len);
    for(i=0;i<len;i++) {
        int result = scanf("%d", &val);
        if (result) {
            append(&arr, val);
        }
    }
    listArr(&arr);
    return 0;
}
