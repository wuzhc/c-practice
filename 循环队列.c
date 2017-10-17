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

/* 初始化队列 */
void init_queue(PQUEUE);
/* 入队 */
void en_queue(PQUEUE,dataType);
/* 出队 */
bool out_queue(PQUEUE,dataType *);
/* 队列是否已满 */
bool is_full_queue(PQUEUE);
/* 判断队列是否为空 */
bool is_empty_queue(PQUEUE);
/* 遍历队列 */
void traverse_queue(PQUEUE);


int main()
{
    QUEUE queue;
    init_queue(&queue);
    en_queue(&queue, 1);
    en_queue(&queue, 2);
    en_queue(&queue, 3);
    en_queue(&queue, 4);

    printf("当前队列元素：");
    traverse_queue(&queue);

    dataType val;
    if (out_queue(&queue, &val)) {
        printf("出队元素为：%d\n", val);
    } else {
        printf("出队失败！\n");
    }

    printf("当前队列元素：");
    traverse_queue(&queue);

    return 0;
}

/* 初始化队列 */
void init_queue(PQUEUE pQ)
{
    pQ->data = (dataType *)malloc(sizeof(dataType)*MAX_LENGTH);
    if (pQ->data == NULL) {
        printf("分配内存失败");
        exit(-1);
    }
    pQ->front = 0; /* 用于标记位置 */
    pQ->rear = 0; /* 用于标记位置 */
}

/* 入队 */
void en_queue(PQUEUE pQ, dataType val)
{
    if (is_full_queue(pQ)) {
        //printf("队列已满\n");
        return ;
    }
    pQ->data[pQ->rear] = val;
    pQ->rear = (pQ->rear + 1) % MAX_LENGTH;
}

/* 出队 */
bool out_queue(PQUEUE pQ, dataType * val)
{
    if (is_empty_queue(pQ)) {
        return false;
    }

    *val = pQ->data[pQ->front];
    pQ->front = (pQ->front+1) % MAX_LENGTH;
}

/* 检测队列是否已满 */
bool is_full_queue(PQUEUE pQ)
{
    if ((pQ->rear+1)%MAX_LENGTH == pQ->front) { /* 当元素达到MAX_LEGTH - 1个时表示队列已满 */
        return true;
    } else {
        return false;
    }
}


/* 判断队列是否为空 */
bool is_empty_queue(PQUEUE pQ)
{
    if (pQ->front == pQ->rear) {
        return true;
    } else {
        return false;
    }
}

/* 遍历队列 */
void traverse_queue(PQUEUE pQ)
{
    if (is_empty_queue(pQ)) {
        //printf("当前队列为空！\n");
        return ;
    }

    int i ;
    for(i=pQ->front;i<pQ->rear;i++){
        printf("%d ",pQ->data[i]);
    }
    printf("\n");
}
