#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

/* �ݹ�ṹ����붨��ṹ�����������ñ��� */
typedef struct Node
{
	int data; /* ָ���� */
	struct Node *next; /* ָ����һ���ڵ��ָ�� */
}NODE, *PNODE;

void init_chain(PNODE pnode); /* ��ʼ������ */
void traverse_chain(PNODE pnode); /* �������� */
bool chain_push(PNODE pnode, int value); /* ���ӽڵ� */
bool remove_node(PNODE pnode, int index); /* ɾ���ڵ� */
void debug();


int main()
{
    NODE node; /* ʵ�����˶��󣬷����˿ռ䣬���ʱ����Ҫmalloc��̬�����ڴ� */
    init_chain(&node);
    chain_push(&node, 1237);
    chain_push(&node, 1237);
    chain_push(&node, 1237);
    chain_push(&node, 1237);
    chain_push(&node, 1237);
    traverse_chain(&node);
}

void init_chain(PNODE pnode)
{
    pnode->data = 0;
    pnode->next = NULL;
}

bool chain_push(PNODE pnode, int value)
{
    PNODE pnew = (PNODE)malloc(sizeof(NODE));
    if (pnew == NULL) {
        printf("��ӽڵ�ʱ�������ڴ�ʧ��\n");
        exit(-1);
    }
    pnew->data = value;
    pnew->next = NULL;

    int i = 0;
    while (pnode->next != NULL) {
        pnode = pnode->next;
    }
    //debug();
    pnode->next = pnew;
    return true;
}

void traverse_chain(PNODE pnode)
{
	for (pnode = pnode->next; pnode != NULL; pnode = pnode->next) {
		printf("%i ", pnode->data);
	}
}

void debug()
{
    printf("�ǲ��ǳ�����\n");
    exit(-1);
}
