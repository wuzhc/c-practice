#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

//����һ������ڵ�
typedef struct Node {
    int data;
    struct Node * pNext;
} NODE, * PNODE;

//����һ��ջ
typedef struct stack {
    PNODE pTop;
    PNODE pBottom;
} STACK, * PSTACK;

//��ʼ��ջ
void init(PSTACK);
//��ջ
void push(PSTACK,int);
//��ջ
void pop(PSTACK,int *);
//����ջ
void traverse(PSTACK);
//ջ�Ƿ�Ϊ��
bool isEmpty(PSTACK);
//���ջ
void clear(PSTACK);


main()
{
    //����ջ
    STACK stack;

    //��ʼ��ջ
    init(&stack);

    //��ջ
    push(&stack,45);
    push(&stack,56);
    push(&stack,77);

    //����ջ
    printf("ջ����Ϊ��");
    traverse(&stack);
    printf("\n");

    //��ջ
	int val;
    pop(&stack,&val);
    printf("\n");

	//���ջ
	//clear(&stack);

    //����ջ
    printf("��ջ������Ϊ��");
    traverse(&stack);
    printf("\n");
}

//��ʼ��ջ
void init(PSTACK pStack)
{
    pStack->pTop=(PNODE)malloc(sizeof(NODE));
    if (pStack->pTop == NULL) {
        printf("�����ڴ�ʧ�ܣ�\n");
        exit(-1);
    }

	pStack->pBottom=pStack->pTop;
	pStack->pBottom->pNext = NULL;
}

//��ջ
void push(PSTACK pStack, int val)
{
	PNODE pNew;
	pNew=(PNODE)malloc(sizeof(NODE));
	pNew->data=val;
	pNew->pNext=pStack->pTop;
	pStack->pTop=pNew;
}

//ջ�Ƿ�Ϊ��
bool isEmpty(PSTACK pStack)
{
	return pStack->pTop == pStack->pBottom ? true : false;
}

//����ջ
void traverse(PSTACK pStack)
{
	if (isEmpty(pStack))
	{
		printf("��ǰջΪ�գ�\b");
		exit(-1);
	}

	PNODE p;
	p = pStack->pTop;
	while(p != pStack->pBottom)
	{
		printf("%d ",p->data);
		p=p->pNext;
	}
	printf("\n");
}

//��ջ
void pop(PSTACK pStack,int * val)
{
	if (isEmpty(pStack))
	{
		printf("��ǰջΪ�գ�\n");
		exit(-1);
	}

	PNODE p;
	p = pStack->pTop;
	val = p->data;
	pStack->pTop=p->pNext;
	free(p);
	printf("��ջ��Ԫ��Ϊ��%d\n",val);
}

//���ջ
void clear(PSTACK pStack)
{
	PNODE pNew = NULL;
	while (pStack->pTop != pStack->pBottom) {
		pNew = pStack->pTop;
		pStack->pTop = pStack->pTop->pNext;
		free(pNew);
	}
}
