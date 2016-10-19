#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

/*节点结构体*/
typedef struct Node {
    int data;
    struct Node * pNext;
}NODE, * PNODE;

//创建联表
PNODE create_list();
//显示链表
void traverse_list(PNODE pHead);
//链表是否为空
bool is_empty(PNODE pHead);
//链表长度
int list_length(PNODE pHead);
//删除指定位置的节点
int delete_node(PNODE pHead, int pos);
//插入新节点
bool insert_node(PNODE pHead, int pos, int val);


main()
{
    PNODE pHead;

    //创建链表
    pHead = create_list();

    //打印链表
    traverse_list(pHead);

    //判断链表是否为空
    if (is_empty(pHead)) {
        printf("当前链表为空!\n");
    } else {
        printf("当前链表不为空!\n");
    }

    //判断链表长度
    printf("当前链表的长度：%d\n", list_length(pHead));

	//插入新节点
	insert_node(pHead, 1, 999);
	printf("------------------新插入节点后的变化-----------------\n");
	printf("新插入的节点是999，位置是1\n");
	traverse_list(pHead);
	printf("当前链表的长度：%d\n", list_length(pHead));

	//删除链表节点
	int hasDel = delete_node(pHead, 2);
	printf("------------------删除节点后的变化-----------------\n");
	printf("删除的节点是%d，位置是2\n", hasDel);
	traverse_list(pHead);
	printf("当前链表的长度：%d\n", list_length(pHead));

}

//创建联表
PNODE create_list()
{
    int i;int len;int val;
    PNODE pHead; //链表首地址
    PNODE pNew;  //新增加的节点
    PNODE pLast; //链表最后一个节点

    //先分配表头
    pHead = (PNODE)malloc(sizeof(NODE));
    if (NULL == pHead) {
        printf("创建表头失败！\n");
        exit(-1);
    }

    //创建一个节点的指针变量，用来保存链表的最后一个节点
    pLast = pHead;
    pLast->pNext = NULL;

    printf("请输入链表个数：");
    scanf("%d", &len);

    for(i=0;i<len;i++) {
        printf("请输入第%d个值：", i+1);
        scanf("%d", &val);

        pNew = (PNODE)malloc(sizeof(NODE));
        if (NULL == pNew) {
            printf("链表分配内存失败！\n");
            exit(-1);
        }
        pNew->data = val;
        pLast->pNext = pNew;
        pNew->pNext = NULL;
        pLast = pNew;         //将新节点作为最后一个节点
    }

    return pHead;
}

//打印链表
void traverse_list(PNODE pHead)
{
    PNODE p = pHead->pNext; //首节点（第一个有效节点）
    while (p != NULL) {
        printf("%d\n",p->data);
        p = p->pNext;
    }
}

//链表是否为空
bool is_empty(PNODE pHead)
{
    return pHead->pNext == NULL;
}

//链表长度
int list_length(PNODE pHead)
{
    int len = 0;
    PNODE p = pHead->pNext; //首节点（第一个有效节点）
    while (p != NULL) {
        ++len;
        p = p->pNext;
    }
    return len;
}

//插入新节点
bool insert_node(PNODE pHead, int pos, int val)
{
	int i = 0;
	PNODE p = pHead;
	while (i<pos-1 && p != NULL) {
		p = p->pNext;
		i++;
	}

	int len = list_length(pHead);
	if (pos<i || pos>len+1) {
        return false;
	}

	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if (NULL == pNew) {
		printf("分配内存失败！\n");
		exit(-1);
	}
	pNew->data = val;
	pNew->pNext = p->pNext;
	p->pNext = pNew;
}

//删除节点
int delete_node(PNODE pHead, int pos)
{
    int i = 0;
	PNODE p = pHead;
	while (i<pos-1 && p != NULL) {
		p = p->pNext;
		i++;
	}

	if (pos<i || pos>list_length(pHead)) {
        return 0;
	}

	PNODE nextNode = p->pNext;
	int val = nextNode->data;
	p->pNext = nextNode->pNext;
	free(nextNode);
	return val;
}
