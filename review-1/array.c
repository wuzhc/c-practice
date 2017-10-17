#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "array.h"


int main()
{
	A a;
	int len;
	int num = 0;
	int value;

	printf("请输入数组的长度：");
	scanf("%d", &len);

	init_array(&a, len);
	printf("\n请输入数组的值: ");
	while (scanf("%d", &value) == 1 && num < len) {
        if (array_push(&a, value)) {
            printf("成功添加%d\n", value);
        } else {
            printf("%d添加失败\n", value);
        }
        num++;
	}

	traverse_array(&a); /* 遍历数组 */
	inverse_array(&a); /* 翻转数组 */
	traverse_array(&a); /* 重新遍历数组 */
	array_pop(&a); /* 删除末尾一个元素 */
	array_pop(&a); /* 删除末尾一个元素 */
	traverse_array(&a);
	array_insert(&a, 0, 111); /* 首位插入新元素111 */
	traverse_array(&a);
    array_insert(&a, 3, 333); /* 试一下插入一个错误的值 */
	traverse_array(&a);
	return 0;
}

void init_array(A *a, int len)
{
	if (len <= 0) {
		return ;
	}

	a->head = (int *)malloc(sizeof(int) * len);
	if (a->head == NULL) {
		printf("创建内存失败\n");
		exit(-1);
	}
	a->len = len;
	a->num = 0;
}

bool array_push(A *a, int value)
{
	if (is_full(a)) {
		printf ("当前数组已满，%d插入失败\n", value);
		return false;
	}

	a->head[a->num] = value;
	a->num++;
	return true;
}

bool is_full(A *a)
{
	if (a->num == a->len) {
		return true;
	} else {
		return false;
	}
}

bool is_empty(A *a)
{
	if (a->num == 0) {
		return true;
	} else {
		return false;
	}
}

void traverse_array(A *a)
{
	if (is_empty(a)) {
		printf("当前数组为空\n");
		exit(-1);
	}

	printf("\n当前数组内容为：\n");
	int i;
	for (i = 0; i < a->num; i++) {
		printf("%i ", a->head[i]);
	}
	printf("\n");
}

void inverse_array(A *a)
{
    if (is_empty(a)) {
        printf("当前数组为空\n");
        exit(-1);
    }

    int end = a->num - 1;
    int start = 0;
    int temp;
    while (start < end) {
        temp = a->head[start];
        a->head[start] = a->head[end];
        a->head[end] = temp;
        start++;
        end--;
    }
}

int array_pop(A *a)
{
    if (is_empty(a)) {
        printf("当前数组为空\n");
        exit(-1);
    }

    a->num--; /* TODO 并没有真正的删除 */
    return a->head[a->num];
}

void array_insert(A *a, int index, int value)
{
    if (is_full(a)) {
        printf("当前数组已满\n");
        exit(-1);
    }

    if (index + 1 > a->len || index < 0) {
        printf("插入位置超过了数组最大长度\n");
        exit(-1);
    }

    if (a->head[index]) {
        int temp;
        int i;
        for (i = a->num; i > index; i--) {
            a->head[i] = a->head[i-1];
        }
    }
    a->head[index] = value;
    a->num++;
}

