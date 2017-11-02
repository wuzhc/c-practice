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

/* 初始化队列 */
void init_queue(PQUEUE);
/* 入队 */
void en_queue(PQUEUE,int);
/* 出队 */
bool out_queue(PQUEUE,int *);
/* 遍历队列 */
void traverse_queue(PQUEUE);
/* 是否为空队列 */
bool is_empty_queue(PQUEUE);

int main()
{
    QUEUE queue;
    init_queue(&queue);

    if (is_empty_queue(&queue)) {
        printf("这是一个空队列\n");
    } else {
        printf("这不是一个空队列\n");
    }

    en_queue(&queue,1);
    en_queue(&queue,2);
    en_queue(&queue,3);
    en_queue(&queue,4);


    int val;
    if (out_queue(&queue, &val)) {
        printf("出队元素为%d\n", val);
    } else {
        printf("出队失败\n");
    }

    if (out_queue(&queue, &val)) {
        printf("出队元素为%d\n", val);
    } else {
        printf("出队失败\n");
    }

    traverse_queue(&queue);
    return 0;
}

/* 初始化队列 */
void init_queue(PQUEUE pQ)
{
    pQ->pRear = pQ->pFront = NULL;
}

/* 入队 */
void en_queue(PQUEUE pQ, int val)
{
    PNODE pNew;
    pNew = (PNODE)malloc(sizeof(NODE));
    if (pNew == NULL) {
        printf("创建内存失败！");
        exit(-1);
    }

    pNew->data = val;
    pNew->pNext = NULL;

    if (pQ->pRear == NULL) {
        pQ->pFront = pQ->pRear = pNew; /* 首次入队时，队头和队尾指向同一个地址 */
    } else {
        pQ->pRear->pNext = pNew;
        pQ->pRear = pNew;
    }
}
/* 出队 */
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

/* 判断队列是否为空 */
bool is_empty_queue(PQUEUE pQ)
{
    if (pQ->pFront == NULL) {
        return true;
    } else {
        return false;
    }
}

/* 遍历队列 */
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

