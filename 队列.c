#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node * pNext;
}NODE, * PNODE;

typedef struct Queue {
    PNODE pFront;
    PNODE pRear;
}QUEUE, * PQUEUE;

/* ��ʼ������ */
void init_queue(PQUEUE);
/* ��� */
void en_queue(PQUEUE,int);
/* ���� */
bool out_queue(PQUEUE,int *);
/* �������� */
void traverse_queue(PQUEUE);
/* �Ƿ�Ϊ�ն��� */
bool is_empty_queue(PQUEUE);

int main()
{
    QUEUE queue;
    init_queue(&queue);

    if (is_empty_queue(&queue)) {
        printf("����һ���ն���\n");
    } else {
        printf("�ⲻ��һ���ն���\n");
    }

    en_queue(&queue,1);
    en_queue(&queue,2);
    en_queue(&queue,3);
    en_queue(&queue,4);


    int val;
    if (out_queue(&queue, &val)) {
        printf("����Ԫ��Ϊ%d\n", val);
    } else {
        printf("����ʧ��\n");
    }

    if (out_queue(&queue, &val)) {
        printf("����Ԫ��Ϊ%d\n", val);
    } else {
        printf("����ʧ��\n");
    }

    traverse_queue(&queue);
    return 0;
}

/* ��ʼ������ */
void init_queue(PQUEUE pQ)
{
    pQ->pRear = pQ->pFront = NULL;
}

/* ��� */
void en_queue(PQUEUE pQ, int val)
{
    PNODE pNew;
    pNew = (PNODE)malloc(sizeof(NODE));
    if (pNew == NULL) {
        printf("�����ڴ�ʧ�ܣ�");
        exit(-1);
    }

    pNew->data = val;
    pNew->pNext = NULL;

    if (pQ->pRear == NULL) {
        pQ->pFront = pQ->pRear = pNew; /* �״����ʱ����ͷ�Ͷ�βָ��ͬһ����ַ */
    } else {
        pQ->pRear->pNext = pNew;
        pQ->pRear = pNew;
    }
}
/* ���� */
bool out_queue(PQUEUE pQ, int * val)
{
    if (is_empty_queue(pQ)) {
        return false;
    } else {
        PNODE p;
        p = pQ->pFront;
        *val = p->data;
        pQ->pFront = p->pNext;
        free(p);
        return true;
    }
}

/* �ж϶����Ƿ�Ϊ�� */
bool is_empty_queue(PQUEUE pQ)
{
    if (pQ->pFront == NULL) {
        return true;
    } else {
        return false;
    }
}

/* �������� */
void traverse_queue(PQUEUE pQ)
{
    if (is_empty_queue(pQ)) {
        return ;
    }
    PNODE p;
    p = pQ->pFront;
    while (p != NULL) {
        printf("%d ",p->data);
        p = p->pNext;
    }
    printf("\n");
}

