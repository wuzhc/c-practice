#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

/*�ڵ�ṹ��*/
typedef struct Node {
    int data;
    struct Node * pNext;
}NODE, * PNODE;

//��������
PNODE create_list();
//��ʾ����
void traverse_list(PNODE pHead);
//�����Ƿ�Ϊ��
bool is_empty(PNODE pHead);
//������
int list_length(PNODE pHead);
//ɾ��ָ��λ�õĽڵ�
int delete_node(PNODE pHead, int pos);
//�����½ڵ�
bool insert_node(PNODE pHead, int pos, int val);
//������ǰ�ƶ�һλ
void left_shift_one(PNODE pHead);
//������ǰ�ƶ�posλ
void left_rotate_string(PNODE pHead, int pos);
//��ת����
void reverse_string(PNODE pHead, int from, int to);
//��ĳ��λ�÷�ת����
void rotate_string(PNODE pHead, int pos);
//����λ�û�ȡ�ڵ�
PNODE get_node_by_pos(PNODE pHead, int pos);
//�Ƿ�Ϊ��������
bool is_palindrome(PNODE pHead);


main()
{
    PNODE pHead;

    //��������
    pHead = create_list();

    //��ӡ����
    traverse_list(pHead);

    //�ж�������
    printf("�������ɹ�������Ϊ��%d\n", list_length(pHead));

    //���������ж�
	if (is_palindrome(pHead)) {
        printf("����һ����������\n\n");
	} else {
        printf("�ⲻ��һ����������\n\n");
	}

    //��ת����������ת��
    int start;
    printf("������ӵڼ�λ��ʼ��ת����:");
    scanf("%d", &start);
    printf("------------------�ӵ�%dλ�ÿ�ʼ��ת�����ı仯-----------------\n", start);
	rotate_string(pHead, start);
    traverse_list(pHead);
	printf("��ǰ����ĳ��ȣ�%d\n", list_length(pHead));

	//�����½ڵ�
	int pos,val;
	printf("�������²���ڵ�λ�ã�");
	scanf("%d", &pos);
	printf("�������½ڵ���ֵ��");
	scanf("%d", &val);
	printf("------------------�²���ڵ��ı仯-----------------\n");
	insert_node(pHead, pos, val);
	printf("�²���Ľڵ���%d��λ����%d\n", val, pos);
	traverse_list(pHead);
	printf("��ǰ����ĳ��ȣ�%d\n\n", list_length(pHead));

	//ɾ������ڵ�
	int delPos;
	printf("������ɾ���ڵ��λ�ã�");
	scanf("%d", &delPos);
	int hasDel = delete_node(pHead, delPos);
	printf("------------------ɾ���ڵ��ı仯-----------------\n");
	printf("ɾ���Ľڵ���%d��λ����%d\n", hasDel, delPos);
	traverse_list(pHead);
	printf("��ǰ����ĳ��ȣ�%d\n\n", list_length(pHead));

}

//��������
PNODE create_list()
{
    int i;int len;int val;
    PNODE pHead; //�����׵�ַ
    PNODE pNew;  //�����ӵĽڵ�
    PNODE pLast; //�������һ���ڵ�

    //�ȷ����ͷ
    pHead = (PNODE)malloc(sizeof(NODE));
    if (NULL == pHead) {
        printf("������ͷʧ�ܣ�\n");
        exit(-1);
    }

    //����һ���ڵ��ָ�����������������������һ���ڵ�
    pLast = pHead;
    pLast->pNext = NULL;

    printf("���������������");
    scanf("%d", &len);

    for(i=0;i<len;i++) {
        printf("�������%d��ֵ��", i+1);
        scanf("%d", &val);

        pNew = (PNODE)malloc(sizeof(NODE));
        if (NULL == pNew) {
            printf("��������ڴ�ʧ�ܣ�\n");
            exit(-1);
        }
        pNew->data = val;
        pLast->pNext = pNew;
        pNew->pNext = NULL;
        pLast = pNew;         //���½ڵ���Ϊ���һ���ڵ�
    }

    return pHead;
}

//��ӡ����
void traverse_list(PNODE pHead)
{
    PNODE p = pHead->pNext; //�׽ڵ㣨��һ����Ч�ڵ㣩
    while (p != NULL) {
        printf("%d\n",p->data);
        p = p->pNext;
    }
}

//�����Ƿ�Ϊ��
bool is_empty(PNODE pHead)
{
    return pHead->pNext == NULL;
}

//������
int list_length(PNODE pHead)
{
    int len = 0;
    PNODE p = pHead->pNext; //�׽ڵ㣨��һ����Ч�ڵ㣩
    while (p != NULL) {
        ++len;
        p = p->pNext;
    }
    return len;
}

//�����½ڵ�
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
		printf("�����ڴ�ʧ�ܣ�\n");
		exit(-1);
	}
	pNew->data = val;
	pNew->pNext = p->pNext;
	p->pNext = pNew;
}

//ɾ���ڵ�
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

//��ת����
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
        pTo = get_node_by_pos(pHead, to-1); //�����ò�����һ���ڵ�,ֻ��ͨ��ѭ���ҳ���
        from++;
        to--;
    }
}

//�Ƿ�Ϊ��������
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
        pBack = get_node_by_pos(pHead, back - 1); //�����ò�����һ���ڵ�,ֻ��ͨ��ѭ���ҳ���
        front++;
        back--;
    }
    return true;
}

//����λ���ҳ��ڵ�
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

//����ת������һ�������һ����k�����磬����Ϊ1��2��3��4��5��6��k=2����ת��2��1��6��5��4��3
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
