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
//链表向前移动一位
void left_shift_one(PNODE pHead);
//链表向前移动pos位
void left_rotate_string(PNODE pHead, int pos);
//翻转链表
void reverse_string(PNODE pHead, int from, int to);
//在某个位置翻转链表
void rotate_string(PNODE pHead, int pos);
//根据位置获取节点
PNODE get_node_by_pos(PNODE pHead, int pos);
//是否为回文链表
bool is_palindrome(PNODE pHead);


main()
{
    PNODE pHead;

    //创建链表
    pHead = create_list();

    //打印链表
    traverse_list(pHead);

    //判断链表长度
    printf("链表创建成功，长度为：%d\n", list_length(pHead));

    //回文链表判断
	if (is_palindrome(pHead)) {
        printf("这是一个回文链表\n\n");
	} else {
        printf("这不是一个回文链表\n\n");
	}

    //翻转链表（暴力翻转）
    int start;
    printf("请输入从第几位开始翻转链表:");
    scanf("%d", &start);
    printf("------------------从第%d位置开始翻转链表后的变化-----------------\n", start);
	rotate_string(pHead, start);
    traverse_list(pHead);
	printf("当前链表的长度：%d\n", list_length(pHead));

	//插入新节点
	int pos,val;
	printf("请输入新插入节点位置：");
	scanf("%d", &pos);
	printf("请输入新节点数值：");
	scanf("%d", &val);
	printf("------------------新插入节点后的变化-----------------\n");
	insert_node(pHead, pos, val);
	printf("新插入的节点是%d，位置是%d\n", val, pos);
	traverse_list(pHead);
	printf("当前链表的长度：%d\n\n", list_length(pHead));

	//删除链表节点
	int delPos;
	printf("请输入删除节点的位置：");
	scanf("%d", &delPos);
	int hasDel = delete_node(pHead, delPos);
	printf("------------------删除节点后的变化-----------------\n");
	printf("删除的节点是%d，位置是%d\n", hasDel, delPos);
	traverse_list(pHead);
	printf("当前链表的长度：%d\n\n", list_length(pHead));

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

//翻转链表
void reverse_string(PNODE pHead, int from, int to)
{
    int t;
    PNODE pFrom,pTo;
    pFrom = get_node_by_pos(pHead, from);
    pTo = get_node_by_pos(pHead, to);

    while(from<to){
        t=pFrom->data;
        pFrom->data=pTo->data;
        pTo->data = t;
        pFrom = pFrom->pNext;
        pTo = get_node_by_pos(pHead, to-1); //单向拿不到上一个节点,只能通过循环找出来
        from++;
        to--;
    }
}

//是否为回文链表
bool is_palindrome(PNODE pHead)
{
    int front = 0;
    int back = list_length(pHead) - 1;
    PNODE pFront, pBack;

    pFront = get_node_by_pos(pHead, front);
    pBack = get_node_by_pos(pHead, back);

    while(front<back)
    {
        if (pFront->data != pBack->data) {
            return false;
        }

        pFront = pFront->pNext;
        pBack = get_node_by_pos(pHead, back - 1); //单向拿不到上一个节点,只能通过循环找出来
        front++;
        back--;
    }
    return true;
}

//根据位置找出节点
PNODE get_node_by_pos(PNODE pHead, int pos)
{
    int i = 0;
    PNODE p = pHead->pNext;

    while(p!=NULL && i<pos){
        p = p->pNext;
        ++i;
    }
    return p;
}

//链表翻转。给出一个链表和一个数k，比如，链表为1→2→3→4→5→6，k=2，则翻转后2→1→6→5→4→3
void rotate_string(PNODE pHead, int pos)
{
    int n;
    int len = list_length(pHead);

    pos %= len;
    reverse_string(pHead, 0, pos-1);

    //traverse_list(pHead);exit(-1);
    if(pos<len){
        reverse_string(pHead,pos,len-1);
    }

}
