#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

//定义一个链表节点
typedef struct Node {
    int data;
    struct Node * pNext;
} NODE, * PNODE;

//定义一个栈
typedef struct stack {
    PNODE pTop;
    PNODE pBottom;
} STACK, * PSTACK;

//初始化栈
void init(PSTACK);
//入栈
void push(PSTACK,int);
//出栈
void pop(PSTACK,int *);
//遍历栈
void traverse(PSTACK);
//栈是否为空
bool isEmpty(PSTACK);
//清空栈
void clear(PSTACK);


main()
{
    //定义栈
    STACK stack;

    //初始化栈
    init(&stack);

    //入栈
    push(&stack,45);
    push(&stack,56);
    push(&stack,77);

    //遍历栈
    printf("栈内容为：");
    traverse(&stack);
    printf("\n");

    //出栈
	int val;
    pop(&stack,&val);
    printf("\n");

	//清空栈
	//clear(&stack);

    //遍历栈
    printf("出栈后内容为：");
    traverse(&stack);
    printf("\n");
}

//初始化栈
void init(PSTACK pStack)
{
    pStack->pTop=(PNODE)malloc(sizeof(NODE));
    if (pStack->pTop == NULL) {
        printf("创建内存失败！\n");
        exit(-1);
    }

	pStack->pBottom=pStack->pTop;
	pStack->pBottom->pNext = NULL;
}

//入栈
void push(PSTACK pStack, int val)
{
	PNODE pNew;
	pNew=(PNODE)malloc(sizeof(NODE));
	pNew->data=val;
	pNew->pNext=pStack->pTop;
	pStack->pTop=pNew;
}

//栈是否为空
bool isEmpty(PSTACK pStack)
{
	return pStack->pTop == pStack->pBottom ? true : false;
}

//遍历栈
void traverse(PSTACK pStack)
{
	if (isEmpty(pStack))
	{
		printf("当前栈为空！\b");
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

//出栈
void pop(PSTACK pStack,int * val)
{
	if (isEmpty(pStack))
	{
		printf("当前栈为空！\n");
		exit(-1);
	}

	PNODE p;
	p = pStack->pTop;
	val = p->data;
	pStack->pTop=p->pNext;
	free(p);
	printf("出栈的元素为：%d\n",val);
}

//清空栈
void clear(PSTACK pStack)
{
	PNODE pNew = NULL;
	while (pStack->pTop != pStack->pBottom) {
		pNew = pStack->pTop;
		pStack->pTop = pStack->pTop->pNext;
		free(pNew);
	}
}
