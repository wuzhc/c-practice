#include "chain.h"

int isEmpty(List L)
{
    return L->Next == NULL;
}

int isLast(Position P)
{
    return P->Next == NULL;
}

void insert(ElementType X, Position P)
{
	Position temp;
	//temp = new struct Node;
	if(temp !=NULL)
	{
		temp->Element = X;
		temp->Next = P->Next;
		P->Next = temp;
	}
	perror("Not enough memory");
}

Position find(ElementType x, List L)
{
    if (L->Next == NULL) {
        return NULL;
    }

    Position P = L->Next;
    while (P != NULL && P->Element != x) {
        P = P->Next;
    }

    return P;
}

List creat(struct Node *head)/*返回的是与节点相同类型的指针*/
{
    struct Node*p1,*p2;
    int i=1;
//③利用malloc ( )函数向系统申请分配一个节点
    p1=p2=(struct Node*)malloc(sizeof(struct Node));/*新节点*/
    printf("请输入值，值小于等于0结束，值存放地址为：p1_ADDR= %d\n",p1);
    scanf("%d",&p1->Element);/*输入节点的值*/
    p1->Next=NULL;/*将新节点的指针置为空*/
    while(p1->Element>0)/*输入节点的数值大于0*/
    {
//④将新节点的指针成员赋值为空。若是空表，将新节点连接到表头；若是非空表，将新节点接到表尾;
        if(head==NULL)
            head=p1;/*空表，接入表头*/
        else
            p2->Next=p1;/*非空表，接到表尾*/
        p2=p1;

        p1=(struct Node*)malloc(sizeof(struct Node));/*下一个新节点*/
        i=i+1;
        printf("请输入值，值小于等于0结束，值存放地址为：p%d_ADDR= %d\n",i,p2);
        scanf("%d",&p1->Element);/*输入节点的值*/
//⑤判断一下是否有后续节点要接入链表，若有转到3 )，否则结束;
    }
     free(p1);  //申请到的没录入，所以释放掉
    p1=NULL;   //使指向空
    p2->Next = NULL; //到表尾了，指向空
    printf("链表输入结束（END）\n");
//==============================================
    return head;/*返回链表的头指针*/
}

void print(List L)/*出以head为头的链表各节点的值*/
{
    List temp;
    temp=L;/*取得链表的头指针*/

    printf("\n\n\n链表存入的值为：\n");
    while(temp!=NULL)/*只要是非空表*/
    {
        printf("%6d\n",temp->Element);/*输出链表节点的值*/
        temp=temp->Next;/*跟踪链表增长*/
    }
    printf("链表打印结束!!");
}

void main()
{
    ptrToNode head;
    head = NULL;
    head = creat(head);
    print(head);
    Position findPos;
    findPos = find(12, head);
    printf("当前的位置为%d", findPos);
}
