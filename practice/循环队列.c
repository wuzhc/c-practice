#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#define MAX_LENGTH 3

typedef int dataType;

typedef struct Queue
{
    dataType *data;
    int front;
    int rear;
} QUEUE, * PQUEUE;

/* ��ʼ������ */
void init_queue(PQUEUE);
/* ��� */
void en_queue(PQUEUE,dataType);
/* ���� */
bool out_queue(PQUEUE,dataType *);
/* �����Ƿ����� */
bool is_full_queue(PQUEUE);
/* �ж϶����Ƿ�Ϊ�� */
bool is_empty_queue(PQUEUE);
/* �������� */
void traverse_queue(PQUEUE);


int main()
{
    QUEUE queue;
    init_queue(&queue);
    en_queue(&queue, 1);
    en_queue(&queue, 2);
    en_queue(&queue, 3);
    en_queue(&queue, 4);

    printf("��ǰ����Ԫ�أ�");
    traverse_queue(&queue);

    dataType val;
    if (out_queue(&queue, &val)) {
        printf("����Ԫ��Ϊ��%d\n", val);
    } else {
        printf("����ʧ�ܣ�\n");
    }

    printf("��ǰ����Ԫ�أ�");
    traverse_queue(&queue);

    return 0;
}

/* ��ʼ������ */
void init_queue(PQUEUE pQ)
{
    pQ->data = (dataType *)malloc(sizeof(dataType)*MAX_LENGTH);
    if (pQ->data == NULL) {
        printf("�����ڴ�ʧ��");
        exit(-1);
    }
    pQ->front = 0; /* ���ڱ��λ�� */
    pQ->rear = 0; /* ���ڱ��λ�� */
}

/* ��� */
void en_queue(PQUEUE pQ, dataType val)
{
    if (is_full_queue(pQ)) {
        //printf("��������\n");
        return ;
    }
    pQ->data[pQ->rear] = val;
    pQ->rear = (pQ->rear + 1) % MAX_LENGTH;
}

/* ���� */
bool out_queue(PQUEUE pQ, dataType * val)
{
    if (is_empty_queue(pQ)) {
        return false;
    }

    *val = pQ->data[pQ->front];
    pQ->front = (pQ->front+1) % MAX_LENGTH;
}

/* �������Ƿ����� */
bool is_full_queue(PQUEUE pQ)
{
    if ((pQ->rear+1)%MAX_LENGTH == pQ->front) { /* ��Ԫ�شﵽMAX_LEGTH - 1��ʱ��ʾ�������� */
        return true;
    } else {
        return false;
    }
}


/* �ж϶����Ƿ�Ϊ�� */
bool is_empty_queue(PQUEUE pQ)
{
    if (pQ->front == pQ->rear) {
        return true;
    } else {
        return false;
    }
}

/* �������� */
void traverse_queue(PQUEUE pQ)
{
    if (is_empty_queue(pQ)) {
        //printf("��ǰ����Ϊ�գ�\n");
        return ;
    }

    int i ;
    for(i=pQ->front;i<pQ->rear;i++){
        printf("%d ",pQ->data[i]);
    }
    printf("\n");
}
