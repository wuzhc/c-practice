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

List creat(struct Node *head)/*���ص�����ڵ���ͬ���͵�ָ��*/
{
    struct Node*p1,*p2;
    int i=1;
//������malloc ( )������ϵͳ�������һ���ڵ�
    p1=p2=(struct Node*)malloc(sizeof(struct Node));/*�½ڵ�*/
    printf("������ֵ��ֵС�ڵ���0������ֵ��ŵ�ַΪ��p1_ADDR= %d\n",p1);
    scanf("%d",&p1->Element);/*����ڵ��ֵ*/
    p1->Next=NULL;/*���½ڵ��ָ����Ϊ��*/
    while(p1->Element>0)/*����ڵ����ֵ����0*/
    {
//�ܽ��½ڵ��ָ���Ա��ֵΪ�ա����ǿձ����½ڵ����ӵ���ͷ�����Ƿǿձ����½ڵ�ӵ���β;
        if(head==NULL)
            head=p1;/*�ձ������ͷ*/
        else
            p2->Next=p1;/*�ǿձ��ӵ���β*/
        p2=p1;

        p1=(struct Node*)malloc(sizeof(struct Node));/*��һ���½ڵ�*/
        i=i+1;
        printf("������ֵ��ֵС�ڵ���0������ֵ��ŵ�ַΪ��p%d_ADDR= %d\n",i,p2);
        scanf("%d",&p1->Element);/*����ڵ��ֵ*/
//���ж�һ���Ƿ��к����ڵ�Ҫ������������ת��3 )���������;
    }
     free(p1);  //���뵽��û¼�룬�����ͷŵ�
    p1=NULL;   //ʹָ���
    p2->Next = NULL; //����β�ˣ�ָ���
    printf("�������������END��\n");
//==============================================
    return head;/*���������ͷָ��*/
}

void print(List L)/*����headΪͷ��������ڵ��ֵ*/
{
    List temp;
    temp=L;/*ȡ�������ͷָ��*/

    printf("\n\n\n��������ֵΪ��\n");
    while(temp!=NULL)/*ֻҪ�Ƿǿձ�*/
    {
        printf("%6d\n",temp->Element);/*�������ڵ��ֵ*/
        temp=temp->Next;/*������������*/
    }
    printf("�����ӡ����!!");
}

void main()
{
    ptrToNode head;
    head = NULL;
    head = creat(head);
    print(head);
    Position findPos;
    findPos = find(12, head);
    printf("��ǰ��λ��Ϊ%d", findPos);
}
