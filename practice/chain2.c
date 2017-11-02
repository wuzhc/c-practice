#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

/* 递归结构体必须定义结构体名，不能用别名 */
typedef struct Node
{
	int data; /* 指针域 */
	struct Node *next; /* 指向下一个节点的指针 */
}NODE, *PNODE;

void init_chain(PNODE pnode); /* 初始化链表 */
void traverse_chain(PNODE pnode); /* 遍历链表 */
bool chain_push(PNODE pnode, int value); /* 增加节点 */
bool remove_node(PNODE pnode, int index); /* 删除节点 */
void debug();


int main()
{
    NODE node; /* 实例化了对象，分配了空间，这个时候不需要malloc动态分配内存 */
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
        printf("添加节点时，分配内存失败\n");
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
    printf("是不是出错了\n");
    exit(-1);
}
