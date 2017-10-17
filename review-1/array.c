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

	printf("����������ĳ��ȣ�");
	scanf("%d", &len);

	init_array(&a, len);
	printf("\n�����������ֵ: ");
	while (scanf("%d", &value) == 1 && num < len) {
        if (array_push(&a, value)) {
            printf("�ɹ����%d\n", value);
        } else {
            printf("%d���ʧ��\n", value);
        }
        num++;
	}

	traverse_array(&a); /* �������� */
	inverse_array(&a); /* ��ת���� */
	traverse_array(&a); /* ���±������� */
	array_pop(&a); /* ɾ��ĩβһ��Ԫ�� */
	array_pop(&a); /* ɾ��ĩβһ��Ԫ�� */
	traverse_array(&a);
	array_insert(&a, 0, 111); /* ��λ������Ԫ��111 */
	traverse_array(&a);
    array_insert(&a, 3, 333); /* ��һ�²���һ�������ֵ */
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
		printf("�����ڴ�ʧ��\n");
		exit(-1);
	}
	a->len = len;
	a->num = 0;
}

bool array_push(A *a, int value)
{
	if (is_full(a)) {
		printf ("��ǰ����������%d����ʧ��\n", value);
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
		printf("��ǰ����Ϊ��\n");
		exit(-1);
	}

	printf("\n��ǰ��������Ϊ��\n");
	int i;
	for (i = 0; i < a->num; i++) {
		printf("%i ", a->head[i]);
	}
	printf("\n");
}

void inverse_array(A *a)
{
    if (is_empty(a)) {
        printf("��ǰ����Ϊ��\n");
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
        printf("��ǰ����Ϊ��\n");
        exit(-1);
    }

    a->num--; /* TODO ��û��������ɾ�� */
    return a->head[a->num];
}

void array_insert(A *a, int index, int value)
{
    if (is_full(a)) {
        printf("��ǰ��������\n");
        exit(-1);
    }

    if (index + 1 > a->len || index < 0) {
        printf("����λ�ó�����������󳤶�\n");
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

