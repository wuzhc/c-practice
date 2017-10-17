#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "chain.h"

int main()
{
	PNODE pnode;
	pnode = init_chain();
	chain_push(pnode, 1);
	chain_push(pnode, 2);
	chain_push(pnode, 3);
	printf("��ǰ����ĳ���Ϊ��%i\n", chain_length(pnode));
	printf("��������Ϊ: \n");
	traverse_chain(pnode);
	printf("�����ڵ�֮����������Ϊ��\n");
	add_node(pnode, 3, 1237);
	traverse_chain(pnode);
	return 0;
}

PNODE init_chain()
{
    PNODE pHead;
	pHead = (PNODE)malloc(sizeof(NODE));
	if (pHead == NULL) {
		printf("��ʼ������ʱ�������ڴ�ʧ��\n");
		exit(-1);
	}
	pHead->data = 0;
	pHead->next = NULL;
	return pHead;
}

bool chain_push(PNODE pnode, int value)
{
	PNODE pNewNode;
	pNewNode = (PNODE)malloc(sizeof(NODE));
	if (pNewNode == NULL) {
		printf("�����½ڵ�ʱ�������ڴ�ʧ��\n");
		exit(-1);
	}

	pNewNode->next = NULL;
	pNewNode->data = value;

	while (pnode->next != NULL) {
        pnode = pnode->next;
	}

	pnode->next = pNewNode;
	return true;
}

void traverse_chain(PNODE pnode)
{
	for (pnode = pnode->next; pnode != NULL; pnode = pnode->next) {
		printf("%i ", pnode->data);
	}
	printf("\n");
}

bool add_node(PNODE pnode, int pos, int value)
{
    int len = chain_length(pnode);
    if (len <= pos +1) { /* �������λ�ó����������ȣ�ֱ��׷����������� */
        return chain_push(pnode, value);
    }

    PNODE pnew = (PNODE)malloc(sizeof(NODE));
    if (pnew == NULL) {
        printf("�����½ڵ�ʱ�������ڴ�ʧ��\n");
        exit(-1);
    }
    pnew->data = value;
    pnew->next = NULL;

    if (len == 0) {
        pnode->next = pnew;
        return true;
    }

    int i;
    PNODE p = pnode;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }

    pnew->next = p->next;
    p->next = pnew;
    return true;
}

int chain_length(PNODE pnode)
{
    int i = 0;
    PNODE p = pnode->next;
    while (p != NULL) {
        p = p->next;
        i++;
    }
    return i;
}

bool is_empty(PNODE pnode)
{
    if (pnode->next == NULL) {
        return false;
    } else {
        return true;
    }
}
